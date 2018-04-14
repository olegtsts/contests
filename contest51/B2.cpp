#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <limits>
#include <algorithm>

void FindMostRemote(
    const std::vector<std::vector<int>>& neighbours,
    const int current_node,
    int& most_remote_node,
    std::vector<bool>& is_visited,
    const int current_distance,
    int& max_distance
) {
    if (is_visited[current_node]) {
        return;
    }
    is_visited[current_node] = true;
    if (max_distance < current_distance) {
        most_remote_node = current_node;
        max_distance = current_distance;
    }
    for (auto& neighbour: neighbours[current_node]) {
        FindMostRemote(neighbours, neighbour, most_remote_node, is_visited, current_distance + 1, max_distance);
    }
}


int GetMostRemoteNode(
    const std::vector<std::vector<int>>& neighbours
) {
    int most_remote_node;
    std::vector<bool> is_visited(neighbours.size(), false);
    int max_distance = std::numeric_limits<int>::min();
    FindMostRemote(neighbours, 0, most_remote_node, is_visited, 0, max_distance);
    return most_remote_node;
}

struct CloseToBlack {
    int distance_to_black;
    int index;

    bool operator<(const CloseToBlack& other) const {
        return std::forward_as_tuple(distance_to_black, index) < std::forward_as_tuple(other.distance_to_black, other.index);
    }
};

void FillDistances(
    const std::vector<std::vector<int>>& neighbours,
    std::vector<int>& distances_of_nodes,
    const int current_node,
    const int current_distance
) {
    if (distances_of_nodes[current_node] != -1) {
        return;
    }
    distances_of_nodes[current_node] = current_distance;
    for(auto& neighbour: neighbours[current_node]) {
        FillDistances(neighbours, distances_of_nodes, neighbour, current_distance + 1);
    }
}

void GetPathToBlack(
    const std::vector<std::vector<int>>& neighbours,
    std::vector<bool>& is_visited,
    const int current_node,
    const std::vector<bool>& is_black,
    std::vector<int>& current_path,
    std::vector<int>& result_path
) {
    if (is_visited[current_node]) {
        return;
    }
    is_visited[current_node] = true;
    if (is_black[current_node] && result_path.size() == 0) {
        result_path = current_path;
        return;
    }
    if (is_black[current_node]) {
        return;
    }
    current_path.push_back(current_node);
    for (auto& neighbour: neighbours[current_node]) {
        GetPathToBlack(neighbours, is_visited, neighbour, is_black, current_path, result_path);
    }
    current_path.pop_back();
}

void RefreshDistances(
    const std::vector<std::vector<int>>& neighbours,
    std::vector<bool>& is_visited,
    const int current_node,
    const std::vector<bool>& is_black,
    std::set<CloseToBlack>& distances,
    std::vector<int>& distances_of_nodes,
    const int current_distance
) {
    if (is_visited[current_node]) {
        return;
    }
    is_visited[current_node] = true;
    if (is_black[current_node]) {
        return;
    }
    distances.erase({distances_of_nodes[current_node],current_node});
    distances_of_nodes[current_node] = current_distance;
    distances.insert({distances_of_nodes[current_node],current_node});
    for (auto& neighbour: neighbours[current_node]) {
        RefreshDistances(neighbours, is_visited, neighbour, is_black, distances, distances_of_nodes, current_distance + 1);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> neighbours(n);
    for (int i = 0; i + 1 < n; ++i) {
        int first_node, second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        neighbours[first_node].push_back(second_node);
        neighbours[second_node].push_back(first_node);
    }
    int most_remote_node = GetMostRemoteNode(neighbours);
    std::vector<bool> is_black(neighbours.size(), false);
    std::set<CloseToBlack> distances;
    std::vector<int> distances_of_nodes(neighbours.size(), -1);
    FillDistances(neighbours, distances_of_nodes, most_remote_node, 0);
    for (int i = 0; i < n; ++i) {
        if (most_remote_node != i) {
            distances.insert({distances_of_nodes[i], i});
        }
    }
    is_black[most_remote_node] = true;
    std::cout << "1 ";
    int covered_nodes_count = 1;
    int outputed_count = 1;
    while (distances.size() > 0) {
        auto distant = *distances.rbegin();
        std::vector<bool> is_visited(n, false);
        std::vector<int> current_path;
        std::vector<int> gray_nodes;
        GetPathToBlack(neighbours, is_visited, distant.index, is_black, current_path, gray_nodes);
        for (auto& node: gray_nodes) {
            is_black[node] = true;
            distances.erase({distances_of_nodes[node], node});
        }
        is_visited = std::vector<bool>(n, false);
        for (auto& node: gray_nodes) {
            for (auto& neighbour: neighbours[node]) {
                if (!is_black[neighbour]) {
                    RefreshDistances(neighbours, is_visited, neighbour, is_black, distances, distances_of_nodes, 1);
                }
            }
        }
        covered_nodes_count += gray_nodes.size();
        std::cout << covered_nodes_count << " ";
        ++outputed_count;
    }
    for (int i = outputed_count; i < n; ++i) {
        std::cout << covered_nodes_count << " ";
    }
    std::cout << std::endl;
    return 0;
}
