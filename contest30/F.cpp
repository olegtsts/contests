#include <vector>
#include <iostream>
#include <set>

int GetLongestPathSize(
    std::vector<std::vector<int>>& neighbours,
    int current_vertex,
    std::vector<bool>& is_visited
) {
    int max_path_size = 0;
    is_visited[current_vertex] = true;
    for (auto& neighbour: neighbours[current_vertex]) {
        if (!is_visited[neighbour]) {
            int child_path = GetLongestPathSize(neighbours, neighbour, is_visited);
            if (child_path > max_path_size) {
                max_path_size = child_path;
            }
        }
    }
    return max_path_size + 1;
}

void GetLongestPath(
    std::vector<std::vector<int>>& neighbours,
    int current_vertex,
    std::vector<bool>& is_visited,
    std::vector<int>& current_path,
    std::vector<int>& target_path
) {
    is_visited[current_vertex] = true;
    current_path.push_back(current_vertex);
    for (auto& neighbour: neighbours[current_vertex]) {
        if (!is_visited[neighbour]) {
            GetLongestPath(neighbours, neighbour, is_visited, current_path, target_path);
        }
    }
    if (current_path.size() > target_path.size()) {
        target_path = current_path;
    }
    current_path.pop_back();
}

int GetLongestPathToLeavesAndUpdateRootOfLonestPath(
    std::vector<std::vector<int>>& neighbours,
    std::vector<bool>& is_visited,
    const int current_vertex,
    int& root_of_longest_path,
    int& longest_path_length,
    int& target_first_child,
    int& target_second_child
) {
    is_visited[current_vertex] = true;
    int longest_subpath = 0;
    int second_longest_subpath = 0;
    int first_child = -1;
    int second_child = -1;
    for (auto& neighbour: neighbours[current_vertex]) {
        if (!is_visited[neighbour]) {
            int path_to_leaf = GetLongestPathToLeavesAndUpdateRootOfLonestPath(
                neighbours, is_visited, neighbour, root_of_longest_path,
                longest_path_length,
                target_first_child,
                target_second_child);
            if (path_to_leaf > longest_subpath) {
                second_longest_subpath = longest_subpath;
                longest_subpath = path_to_leaf;
                second_child = first_child;
                first_child = neighbour;
            } else if (path_to_leaf > second_longest_subpath) {
                second_longest_subpath = path_to_leaf;
                second_child = neighbour;
            }
        }
    }
    if (longest_subpath + second_longest_subpath + 1 > longest_path_length) {
        longest_path_length = longest_subpath + second_longest_subpath + 1;
        root_of_longest_path = current_vertex;
        target_first_child = first_child;
        target_second_child = second_child;
    }
    return longest_subpath + 1;
}

std::vector<int> GetLongestPathInTree(
    std::vector<std::vector<int>>& neighbours,
    const int n
) {
    std::vector<bool> is_visited(n, false);
    int root_of_longest_path, longest_path_length, target_first_child, target_second_child;
    GetLongestPathToLeavesAndUpdateRootOfLonestPath(neighbours, is_visited, 0,
                                                    root_of_longest_path, longest_path_length,
                                                    target_first_child, target_second_child);

    is_visited = std::vector<bool>(n, false);
    is_visited[root_of_longest_path] = true;
    std::vector<int> first_path_part;
    if (target_first_child >= 0) {
        std::vector<int> current_path;
        GetLongestPath(neighbours, target_first_child, is_visited, current_path, first_path_part);
    }
    std::vector<int> second_path_part;
    if (target_second_child >= 0) {
        std::vector<int> current_path;
        GetLongestPath(neighbours, target_second_child, is_visited, current_path, second_path_part);
    }
    std::vector<int> result_path;
    std::copy(first_path_part.rbegin(), first_path_part.rend(), std::back_inserter(result_path));
    result_path.push_back(root_of_longest_path);
    std::copy(second_path_part.begin(), second_path_part.end(), std::back_inserter(result_path));
    return result_path;
}

struct LeftMostLengths {
    int index;
    int length;

    bool operator<(const LeftMostLengths& other) const {
        return (index + length) < (other.index + other.length) || (
            (index + length) == (other.index + other.length)
            && index < other.index
        );
    }
};

struct RightMostLengths {
    int index;
    int length;

    bool operator<(const RightMostLengths& other) const {
        return (length - index) < (other.length - other.index) || (
            (length - index) == (other.length - other.index)
            && index < other.index
        );
    }
};

int main() {
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
    std::vector<int> longest_path = GetLongestPathInTree(neighbours, n);
    std::vector<bool> is_visited(n, false);
    for (auto& node: longest_path) {
        is_visited[node] = true;
    }
    std::vector<int> longest_paths_sizes(longest_path.size(), 0);
    for (size_t i = 0; i < longest_path.size(); ++i) {
        longest_paths_sizes[i] = GetLongestPathSize(neighbours, longest_path[i], is_visited);
    }
    int left_index = 0;
    int right_index = static_cast<int>(longest_path.size()) - 1;
    std::set<LeftMostLengths> left_most_lengths;
    std::set<RightMostLengths> right_most_lengths;
    for (int i = 0; i < (static_cast<int>(longest_path.size()) + 1) / 2; ++i) {
        left_most_lengths.insert({i, longest_paths_sizes[i]});
        int j = static_cast<int>(longest_path.size()) - i - 1;
        right_most_lengths.insert({j, longest_paths_sizes[j]});
    }
    while (left_index <= right_index) {
        left_most_lengths.erase({left_index, longest_paths_sizes[left_index]});
        left_most_lengths.erase({right_index, longest_paths_sizes[right_index]});
        right_most_lengths.erase({left_index, longest_paths_sizes[left_index]});
        right_most_lengths.erase({right_index, longest_paths_sizes[right_index]});
        int max_distance = left_index;
        if (left_most_lengths.size() == 0) {
            break;
        }
        auto max_left_most_index = left_most_lengths.rbegin()->index;
        auto max_right_most_index = right_most_lengths.rbegin()->index;
        if (
            max_distance >= max_left_most_index - left_index + longest_paths_sizes[max_left_most_index] - 1
            && max_distance >= right_index - max_right_most_index + longest_paths_sizes[max_right_most_index] - 1
        ) {
            break;
        }
        ++left_index;
        --right_index;
    }
    auto first_vertex = longest_path[left_index];
    auto second_vertex = longest_path[right_index];
    if (second_vertex == first_vertex && second_vertex != 0) {
        second_vertex = 0;
    } else if (second_vertex == first_vertex && second_vertex == 0) {
        second_vertex = 1;
    }
    std::cout << first_vertex + 1 << " " << second_vertex + 1 << std::endl;
    return 0;
}
