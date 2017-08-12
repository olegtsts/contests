#include <iostream>
#include <vector>
#include <iomanip>

long double dfs(
    const int current_vertex,
    std::vector<bool>& already_was,
    std::vector<std::vector<int>>& children
) {
    already_was[current_vertex] = true;
    long double sum_not_visited = 0;
    int count_not_visited = 0;
    for (auto& neighbour: children[current_vertex]) {
        if (!already_was[neighbour]) {
            sum_not_visited += dfs(neighbour, already_was, children);
            ++count_not_visited;
        }
    }
    if (count_not_visited == 0) {
        return 0;
    } else {
        return 1 + sum_not_visited / count_not_visited;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> children(n);
    for (int i = 0; i + 1 < n; ++i) {
        int from, to;
        std::cin >> from >> to;
        --from;
        --to;
        children[from].push_back(to);
        children[to].push_back(from);
    }
    std::vector<bool> already_was(n);
    std::cout << std::setprecision(10) << dfs(0, already_was, children) << std::endl;
    return 0;
}
