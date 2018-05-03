#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <unordered_set>

struct NodeData {
    int distance_to_target = std::numeric_limits<int>::max();
    int next_node = -1;
    bool is_visited = false;
};

void GetDistances(
    const std::vector<std::vector<int>>& neighbours,
    const int current_node,
    const int target_node,
    std::vector<NodeData>& data
) {
    if (data[current_node].is_visited) {
        return;
    }
    data[current_node].is_visited = true;
    int min_distance = std::numeric_limits<int>::max();
    int neighbour_with_min_distance = -1;
    for (auto neighbour: neighbours[current_node]) {
        GetDistances(neighbours, neighbour, target_node, data);
        if (min_distance > data[neighbour].distance_to_target) {
            min_distance = data[neighbour].distance_to_target;
            neighbour_with_min_distance = neighbour;
        }
    }
    if (neighbour_with_min_distance != -1) {
        data[current_node].distance_to_target = min_distance + 1;
        data[current_node].next_node = neighbour_with_min_distance;
    }
}

std::vector<int> GetBestStraightPath(
    const std::vector<std::vector<int>>& neighbours,
    const int n
) {
    std::vector<NodeData> data(n);
    data[n - 1].distance_to_target = 0;
    data[n - 1].is_visited = true;
    GetDistances(neighbours, 0, n - 1, data);
    if (data[0].distance_to_target != std::numeric_limits<int>::max()) {
        std::vector<int> result_data;
        int current_node = 0;
        while (current_node != n - 1) {
            result_data.push_back(current_node);
            current_node = data[current_node].next_node;
        }
        result_data.push_back(n - 1);
        return result_data;
    } else {
        return {};
    }
}

std::vector<int> FindSimpleCycle(
     const std::vector<std::vector<int>>& neighbours,
     const int source_node,
     const std::unordered_set<int>& all_nodes

) {
    std::unordered_set<int> not_connected_to_source = all_nodes;
    for (auto neighbour: neighbours[source_node]) {
        not_connected_to_source.erase(neighbour);
    }
    not_connected_to_source.erase(source_node);
    for (auto neighbour: neighbours[source_node]) {
        for (auto second_neighbour: neighbours[neighbour]) {
            if (not_connected_to_source.count(second_neighbour)) {
                return {source_node, neighbour, second_neighbour, source_node};
            }
        }
    }
    return {};
}

void GetComponentSize(
    std::unordered_set<int>& new_visited,
    const std::vector<std::vector<int>>& neighbours,
    const int current_node
) {
    if (new_visited.count(current_node)) {
        return;
    }
    new_visited.insert(current_node);
    for (auto neighbour: neighbours[current_node]) {
        GetComponentSize(new_visited, neighbours, neighbour);
    }
}

struct NotConnectedInfo {
    bool is_there_node = false;
    int first_node;
    int second_node;
};

NotConnectedInfo GetNotConnectedInfo(
    std::unordered_set<int>& new_visited,
    std::unordered_set<int>& all_nodes,
    const std::vector<std::vector<int>>& neighbours,
    const int current_node
) {
    if (new_visited.count(current_node)) {
        return {false, 0, 0};
    }
    new_visited.insert(current_node);
    if (neighbours[current_node].size() != all_nodes.size()) {
        std::unordered_set<int> no_edge_node = all_nodes;
        for (auto neighbour: neighbours[current_node]) {
            no_edge_node.erase(neighbour);
        }
        no_edge_node.erase(current_node);
        return {true, current_node, *no_edge_node.begin()};
    } else {
        for (auto neighbour: neighbours[current_node]) {
            auto info = GetNotConnectedInfo(new_visited, all_nodes, neighbours, neighbour);
            if (info.is_there_node) {
                return info;
            }
        }
        return {false, 0, 0};
    }
}

void GetPath(
    std::unordered_set<int>& new_visited,
    const std::vector<std::vector<int>>& neighbours,
    const int current_node,
    const int target_node,
    std::vector<int>& current_path,
    std::vector<int>& result_path
) {
    if (new_visited.count(current_node)) {
        return;
    }
    new_visited.insert(current_node);
    current_path.push_back(current_node);
    if (current_node == target_node) {
        result_path = current_path;
    }
    for (auto neighbour: neighbours[current_node]) {
        GetPath(new_visited, neighbours, neighbour, target_node, current_path, result_path);
    }
    current_path.pop_back();
}


std::vector<int> GetBestCyclicPath(
    const std::vector<std::vector<int>>& neighbours,
    const int n
) {
    std::unordered_set<int> not_connected_to_dest_directly;
    for (int i = 0; i < n; ++i) {
        not_connected_to_dest_directly.insert(i);
    }
    for (auto neighbour: neighbours[n - 1]) {
        not_connected_to_dest_directly.erase(neighbour);
    }
    if (not_connected_to_dest_directly.count(0) == 0) {
        return {};
    }
    std::vector<std::vector<int>> resticted_neighbours(n);
    for (int i = 0; i < n; ++i) {
        for (auto neighbour: neighbours[i]) {
            if (not_connected_to_dest_directly.count(i) && not_connected_to_dest_directly.count(neighbour)) {
                resticted_neighbours[i].push_back(neighbour);
            }
        }
    }
    auto first_cyclic_pretender = FindSimpleCycle(resticted_neighbours, 0, not_connected_to_dest_directly);
    if (first_cyclic_pretender.size()) {
        first_cyclic_pretender.push_back(n - 1);
        return first_cyclic_pretender;
    } else {
        std::vector<bool> is_visited(n, false);
        is_visited[0] = true;
        for (auto node: resticted_neighbours[0]) {
            if (!is_visited[node]) {
                std::unordered_set<int> new_visited;
                new_visited.insert(0);
                GetComponentSize(new_visited, resticted_neighbours, node);
                std::unordered_set<int> all_nodes = new_visited;
                all_nodes.erase(0);
                new_visited.clear();
                new_visited.insert(0);
                auto info = GetNotConnectedInfo(new_visited, all_nodes, resticted_neighbours, node);
                if (info.is_there_node) {
                    //...
                    new_visited.clear();
                    new_visited.insert(0);
                    std::vector<int> current_path;
                    std::vector<int> result_path;
                    GetPath(new_visited, resticted_neighbours, info.first_node, info.second_node, current_path, result_path);
                    std::unordered_set<int> reachable_from_first;
                    for (auto neighbour: resticted_neighbours[info.first_node]) {
                        reachable_from_first.insert(neighbour);
                    }
                    size_t index = 0;
                    for (index = 1; index < result_path.size(); ++index) {
                        if (reachable_from_first.count(result_path[index]) == 0) {
                            break;
                        }
                    }
                    return {0, info.first_node, result_path[index - 1], result_path[index], info.first_node, n - 1};
                }
                for (auto node: new_visited) {
                    is_visited[node] = true;
                }
            }
        }
        return {};
    }
}


void OutputPath(const std::vector<int>& path_to_output) {
    std::cout << path_to_output.size() - 1 << std::endl;
    for (auto node: path_to_output) {
        std::cout << node + 1 << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> neighbours(n);
    for (int i = 0; i < m; ++i) {
        int first_node, second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        neighbours[first_node].push_back(second_node);
        neighbours[second_node].push_back(first_node);
    }
    auto straight_path = GetBestStraightPath(neighbours, n);
    auto cyclic_path = GetBestCyclicPath(neighbours, n);
    std::vector<int> result_path;
    if (straight_path.size() && cyclic_path.size()) {
        if (straight_path.size() < cyclic_path.size()) {
            result_path = straight_path;
        } else {
            result_path = cyclic_path;
        }
    } else if (straight_path.size()) {
        result_path = straight_path;
    } else {
        result_path = cyclic_path;
    }
    if (result_path.size()) {
        OutputPath(result_path);
    } else {
        std::cout << "-1\n";
    }
    return 0;
}
