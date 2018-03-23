#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cassert>

class DSU {
public:
    DSU(const int n)
        : parent(n)
    {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int GetParent(const int index) {
        if (index == parent[index]) {
            return index;
        } else {
            parent[index] = GetParent(parent[index]);
            return parent[index];
        }
    }

    void Join(const int first_index, const int second_index) {
        parent[GetParent(first_index)] = GetParent(second_index);
    }
private:
    std::vector<int> parent;
};

void DFS(
    std::vector<std::vector<int>>& neighbours,
    DSU& reachability_classes_dsu,
    const int current_node,
    std::vector<bool>& is_visited,
    std::vector<int>& nodes_path,
    std::vector<int>& class_last_depth
) {
    if (is_visited[current_node]) {
        int class_index = reachability_classes_dsu.GetParent(current_node);
        if (class_last_depth[class_index] != -1) {
            for (int i = class_last_depth[class_index]; i < static_cast<int>(nodes_path.size()); ++i) {
                class_last_depth[reachability_classes_dsu.GetParent(nodes_path[i])] = -1;
                reachability_classes_dsu.Join(current_node, nodes_path[i]);
            }
            class_last_depth[reachability_classes_dsu.GetParent(current_node)] = static_cast<int>(nodes_path.size()) - 1;
        }
    } else {
        nodes_path.push_back(current_node);
        is_visited[current_node] = true;
        class_last_depth[reachability_classes_dsu.GetParent(current_node)] = static_cast<int>(nodes_path.size()) - 1;
        for (auto& neighbour: neighbours[current_node]) {
            DFS(neighbours, reachability_classes_dsu, neighbour, is_visited, nodes_path, class_last_depth);
        }
        int class_index = reachability_classes_dsu.GetParent(nodes_path.back());
        nodes_path.pop_back();
        class_last_depth[class_index] = -1;
        if (nodes_path.size() > 0 && reachability_classes_dsu.GetParent(nodes_path.back()) == class_index) {
            class_last_depth[class_index] = static_cast<int>(nodes_path.size()) - 1;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int m,n,h;
    std::cin >> n >> m >> h;
    std::vector<int> off_times(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> off_times[i];
    }
    std::vector<std::vector<int>> neighbours(n);
    for (int i = 0; i < m; ++i) {
        int first_node, second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        if ((off_times[first_node] + 1) % h == off_times[second_node]) {
            neighbours[first_node].push_back(second_node);
        }
        if ((off_times[second_node] + 1) % h == off_times[first_node]) {
            neighbours[second_node].push_back(first_node);
        }
    }
    DSU reachability_classes_dsu(n);
    std::vector<bool> is_visited(n);
    std::vector<int> class_last_depth(n, -1);
    std::vector<int> nodes_path;
    for (int i = 0; i < n; ++i) {
        if (!is_visited[i]) {
            DFS(
                neighbours,
                reachability_classes_dsu,
                i,
                is_visited,
                nodes_path,
                class_last_depth
            );
        }
    }
    std::vector<int> classes_size(n, 0);
    std::vector<bool> does_class_exist(n, false);
    std::vector<bool> does_class_have_outer_edges(n, false);
    for (int i = 0; i < n; ++i) {
        int class_index = reachability_classes_dsu.GetParent(i);
        does_class_exist[class_index] = true;
        for (auto& neighbour: neighbours[i]) {
            if (reachability_classes_dsu.GetParent(neighbour) != class_index) {
                does_class_have_outer_edges[class_index] = true;
            }
        }
        ++classes_size[class_index];
    }
    int min_size = std::numeric_limits<int>::max();
    int min_class_index = -1;
    for (int i = 0; i < n; ++i) {
        if (!does_class_have_outer_edges[i] && does_class_exist[i] && classes_size[i] < min_size) {
            min_size = classes_size[i];
            min_class_index = i;
        }
    }
    if (min_class_index >= 0) {
        std::cout << classes_size[min_class_index] << std::endl;
        for (int i = 0; i < n; ++i) {
            if (reachability_classes_dsu.GetParent(i) == min_class_index) {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << std::endl;
    } else {
        assert(false);
    }
    return 0;
}
