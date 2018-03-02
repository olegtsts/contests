#include <iostream>
#include <vector>
#include <algorithm>

int EVEN_MASK = 1;
int ODD_MASK = 2;

void BottomToTopDFS(
    std::vector<std::vector<int>>& parents,
    std::vector<int>& visited_mask,
    std::vector<int>& dfs_path,
    std::vector<int>& result_path,
    const bool is_even,
    const int current_node,
    const int target_node
) {
    if (is_even && (visited_mask[current_node] & EVEN_MASK)) {
        return;
    }
    if (!is_even && (visited_mask[current_node] & ODD_MASK)) {
        return;
    }
    visited_mask[current_node] |= (is_even ? EVEN_MASK : ODD_MASK);
    dfs_path.push_back(current_node);
    if (current_node == target_node && !is_even) {
        result_path = dfs_path;
    }
    for (auto& parent: parents[current_node]) {
        BottomToTopDFS(parents, visited_mask, dfs_path, result_path, !is_even, parent, target_node);
    }
    dfs_path.pop_back();
}

void TopToBottomDFS(
    std::vector<std::vector<int>>& children,
    const int current_node,
    std::vector<bool>& currently_visited,
    std::vector<bool>& is_visited,
    bool& is_there_cycle
) {
    if (currently_visited[current_node]) {
        is_there_cycle = true;
    }
    if (is_visited[current_node]) {
        return;
    }
    currently_visited[current_node] = true;
    is_visited[current_node] = true;
    for (auto& child: children[current_node]) {
        TopToBottomDFS(children, child, currently_visited, is_visited, is_there_cycle);
    }
    currently_visited[current_node] = false;
}

int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> parents(n);
    std::vector<std::vector<int>> children(n);

    for (int i = 0; i < n; ++i) {
        int count_of_parents;
        std::cin >> count_of_parents;
        for (int j = 0; j < count_of_parents; ++j) {
            int child;
            std::cin >> child;
            --child;
            parents[child].push_back(i);
            children[i].push_back(child);
        }
    }
    int target_pos;
    std::cin >> target_pos;
    --target_pos;
    std::vector<int> visited_mask(n, 0);
    std::vector<int> dfs_path;
    std::vector<int> result_path;
    for (int i = 0; i < n; ++i) {
        if (children[i].size() == 0) {
            BottomToTopDFS(parents, visited_mask, dfs_path, result_path, true, i, target_pos);
        }
    }
    std::vector<bool> is_visited(n, false);
    std::vector<bool> currently_visited(n, false);
    bool is_there_cycle = false;
    TopToBottomDFS(children, target_pos, currently_visited, is_visited, is_there_cycle);
    int mask = visited_mask[target_pos];
    if (mask & ODD_MASK) {
        std::cout << "Win\n";
        std::reverse(result_path.begin(), result_path.end());
        for (size_t i = 0; i < result_path.size(); ++i) {
            std::cout << result_path[i] + 1;
            if (i + 1 < result_path.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    } else if (is_there_cycle) {
        std::cout << "Draw\n";
    } else {
        std::cout << "Lose\n";
    }
    return 0;
}
