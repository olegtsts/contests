#include <iostream>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <set>
#include <utility>
#include <queue>
#include <cassert>
#include <algorithm>


void EraseNodeAndUpdateValences(
    int node,
    std::vector<std::unordered_set<int>>* graph,
    std::set<std::pair<int, int>>* valence_node,
    std::vector<bool>* is_node_removed
) {
    std::unordered_set<int> other_nodes = (*graph)[node];
    (*is_node_removed)[node] = true;
    (*valence_node).erase(std::make_pair((*graph)[node].size(), node));
    for (auto other_node : other_nodes) {
        (*valence_node).erase(std::make_pair((*graph)[other_node].size(), other_node));
        (*graph)[other_node].erase(node);
        (*graph)[node].erase(other_node);
        if (!(*is_node_removed)[other_node]) {
            (*valence_node).insert(std::make_pair((*graph)[other_node].size(), other_node));
        }
    }
}

std::vector<int> RemoveSmallClustersAndGetCenters(
    std::vector<std::unordered_set<int>>* graph,
    int sqrt_lower,
    int sqrt_upper
) {

    std::set<std::pair<int, int>> valence_node;
    for (size_t i = 0; i < graph->size(); ++i) {
        valence_node.insert(std::make_pair((*graph)[i].size(), i));
    }
    std::vector<bool> is_node_removed(graph->size(), false);
    std::vector<int> cluster_centers;
    while (valence_node.size() > 0 &&
           valence_node.begin()->first < sqrt_lower &&
           static_cast<int>(cluster_centers.size()) < sqrt_upper) {
        int node = valence_node.begin()->second;
        std::unordered_set<int> another_nodes = (*graph)[node];
        EraseNodeAndUpdateValences(node, graph, &valence_node, &is_node_removed);
        for (auto another_node : another_nodes) {
            EraseNodeAndUpdateValences(another_node, graph, &valence_node, &is_node_removed);
        }
        cluster_centers.push_back(node);
    }
    return cluster_centers;
}

std::vector<int> GetLoop(
    const std::vector<std::unordered_set<int>>& graph,
    int sqrt_upper
) {
    int start_node = -1;
    for (size_t i = 0; i < graph.size(); ++i) {
        if (graph[i].size() > 0) {
            start_node = i;
            break;
        }
    }
    assert(start_node >= 0);
    std::vector<int> nodes;
    std::unordered_set<int> nodes_set;
    std::queue<int> last_nodes;
    std::unordered_set<int> last_nodes_set;
    int current_node = start_node;
    while (true) {
        nodes.push_back(current_node);
        nodes_set.insert(current_node);
        last_nodes.push(current_node);
        last_nodes_set.insert(current_node);
        while (static_cast<int>(last_nodes.size()) > sqrt_upper - 1) {
            last_nodes_set.erase(last_nodes.front());
            last_nodes.pop();
        }
        for (auto next_node : graph[current_node]) {
            if (last_nodes_set.count(next_node) == 0) {
                current_node = next_node;
                break;
            }
        }
        if (nodes_set.count(current_node) > 0) {
            break;
        }
    }
    std::vector<int> cycle;
    bool start_writing = false;
    for (auto node : nodes) {
        if (node == current_node) {
            start_writing = true;
        }
        if (start_writing) {
            cycle.push_back(node);
        }
    }
    return cycle;
}


int main() {
    std::ios::sync_with_stdio(false);
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<std::unordered_set<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int first_node, second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        graph[first_node].insert(second_node);
        graph[second_node].insert(first_node);
    }
    int sqrt_lower = static_cast<int>(std::sqrt(static_cast<double>(n)));
    int sqrt_upper;
    if (sqrt_lower * sqrt_lower < n) {
        sqrt_upper = sqrt_lower + 1;
    } else {
        sqrt_upper = sqrt_lower;
    }
    std::vector<int> cluster_centers = RemoveSmallClustersAndGetCenters(&graph, sqrt_lower, sqrt_upper);
    if (static_cast<int>(cluster_centers.size()) >= sqrt_upper) {
        std::cout << 1 << std::endl;
        for (int i = 0; i < sqrt_upper; ++i) {
            std::cout << cluster_centers[i] + 1 << " ";
        }
        std::cout << std::endl;
        return 0;
    }
    std::vector<int> cycle = GetLoop(graph, sqrt_upper);
    std::cout << 2 << std::endl;
    std::cout << cycle.size() << std::endl;
    for (auto node : cycle) {
        std::cout << node + 1 << " ";
    }
    std::cout << std::endl;

    return 0;
}
