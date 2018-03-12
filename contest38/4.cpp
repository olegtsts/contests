#include <iostream>
#include <vector>

void DoDFS(
    const int vertex,
    std::vector<bool>& are_connected,
    std::vector<bool>& is_left_component,
    std::vector<bool>& is_visited,
    bool& is_possible,
    bool is_left,
    const int n
) {
    if (is_visited[vertex]) {
        if (is_left_component[vertex] != is_left) {
            is_possible = false;
        }
    } else {
        is_visited[vertex] = true;
        is_left_component[vertex] = is_left;
        for (int i = 0; i < n; ++i) {
            if (i != vertex && !are_connected[i * n + vertex]) {
                DoDFS(i, are_connected, is_left_component, is_visited, is_possible, !is_left, n);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<bool> are_connected(n * n, false);
    for (int i = 0; i < m; ++i) {
        int a,b;
        std::cin >> a >> b;
        --a;
        --b;
        are_connected[a * n + b] = true;
        are_connected[b * n + a] = true;
    }
    std::vector<bool> is_left_component(n, false);
    std::vector<bool> is_visited(n, false);
    bool is_possible = true;
    for (int i = 0; i < n; ++i) {
        if (!is_visited[i]) {
            DoDFS(i, are_connected, is_left_component, is_visited, is_possible, is_left_component[i], n);
        }
    }
    if (is_possible) {
        size_t count_one_part = 0;
        for (int i = 0; i < n; ++i) {
            if (is_left_component[i]) {
                ++count_one_part;
            }
        }
        if (count_one_part == 0) {
            count_one_part = 1;
            is_left_component[0] = true;
        }
        std::cout << count_one_part << std::endl;
        for (int i = 0; i < n; ++i) {
            if (is_left_component[i]) {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << std::endl;
        for (int i = 0; i < n; ++i) {
            if (!is_left_component[i]) {
                std::cout << i + 1 << " ";
            }
        }
    } else {
        std::cout << "-1\n" << std::endl;
    }
    return 0;
}
