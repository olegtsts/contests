#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <unordered_map>
#include <functional>

int MODULO = 1000000007;

class Graph {
public:
    Graph(const int size): graph(size), reverse_graph(size) {}
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    void AddEdge(int source_node, int dest_node) {
        graph[source_node].insert(dest_node);
        reverse_graph[dest_node].insert(source_node);
    }

    void RemoveEdge(int source_node, int dest_node) {
        graph[source_node].erase(dest_node);
        reverse_graph[dest_node].erase(source_node);
    }

    void RemoveNode(int node) {
        auto direct_children = graph[node];
        auto reserve_children = reverse_graph[node];
        for (auto child : direct_children) {
            reverse_graph[child].erase(node);
        }
        for (auto child : reserve_children) {
            graph[child].erase(node);
        }
        reverse_graph[node].clear();
        graph[node].clear();
    }

    void CommonDFS(int node,
                   const std::vector<std::unordered_set<int>>& input_graph,
                   std::vector<bool>* is_visited,
                   const std::function<void(int)>& func) {
        if ((*is_visited)[node]) {
            return;
        }
        (*is_visited)[node] = true;
        for (const int child : input_graph[node]) {
            CommonDFS(child, input_graph, is_visited, func);
        }
        func(node);
    }

    std::vector<bool> GetReachabilityToZero() {
        std::vector<bool> is_visited(graph.size(), false);
        CommonDFS(0, reverse_graph, &is_visited, [](int){});
        return is_visited;
    }

    bool IsThereNonIsolatedCycle(const std::vector<int>& init_nodes) {
        std::vector<bool> is_visited(graph.size(), false);
        for (int node : init_nodes) {
            std::vector<int> root_path_nodes;
            std::unordered_map<int, int> root_path_node_index;
            if (IsThereNonIsolatedCycle(
                node, &root_path_node_index,
                &root_path_nodes, &is_visited)) {
                return true;
            }
        }
        return false;
    }

    bool IsThereNonIsolatedCycle(
        int node,
        std::unordered_map<int, int>* root_path_node_index,
        std::vector<int>* root_path_nodes,
        std::vector<bool>* is_visited
    ) {
        if (root_path_node_index->count(node)) {
            for (size_t index = (*root_path_node_index)[node]; index < root_path_nodes->size(); ++index) {
                int loop_node = (*root_path_nodes)[index];
                if (graph[loop_node].size() > 1) {
                    return true;
                }
            }
        }
        if ((*is_visited)[node]) {
            return false;
        }
        (*is_visited)[node] = true;
        (*root_path_node_index)[node] = root_path_nodes->size();
        root_path_nodes->push_back(node);
        for (auto child : graph[node]) {
            if (IsThereNonIsolatedCycle(
                    child, root_path_node_index, root_path_nodes,
                    is_visited)) {
                return true;
            }
        }
        (*root_path_node_index).erase(node);
        root_path_nodes->pop_back();
        return false;
    }

    std::vector<int> GetTopSort(
        const std::vector<int>& init_nodes
    ) {
        std::vector<bool> is_visited(graph.size(), false);
        std::vector<int> top_sorted;
        for (auto node : init_nodes) {
            CommonDFS(node, graph, &is_visited, [&top_sorted](int node) { top_sorted.push_back(node); });
        }
        std::reverse(top_sorted.begin(), top_sorted.end());
        return top_sorted;
    }

    std::unordered_set<int> GetChildNodes(int node) const {
        return graph[node];
    }
private:
    std::vector<std::unordered_set<int>> graph;
    std::vector<std::unordered_set<int>> reverse_graph;
};

std::string ProcessTestCase() {
    int m;
    std::cin >> m;
    Graph graph(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 2; ++j) {
            int other_metal;
            std::cin >> other_metal;
            graph.AddEdge(i, other_metal - 1);
        }
    }
    std::vector<int> quantities(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> quantities[i];
    }

    std::vector<bool> reachability_to_zero = graph.GetReachabilityToZero();
    std::vector<int> init_nodes;
    for (int i = 0; i < m; ++i) {
        if (!reachability_to_zero[i]) {
            graph.RemoveNode(i);
        } else if (quantities[i] > 0) {
            init_nodes.push_back(i);
        }
    }
    if (graph.IsThereNonIsolatedCycle(init_nodes)) {
        return "UNBOUNDED";
    }
    for (auto node : graph.GetChildNodes(0)) {
        graph.RemoveEdge(0, node);
    }
    std::vector<int> top_sort = graph.GetTopSort(init_nodes);
    for (auto node : top_sort) {
        for (auto child_node : graph.GetChildNodes(node)) {
            quantities[child_node] += quantities[node];
            quantities[child_node] %= MODULO;
        }
    }
    return std::to_string(quantities[0]);
}


int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ": " << ProcessTestCase() << std::endl;
    }
    return 0;
}
