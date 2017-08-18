#include <iostream>
#include <vector>
#include <utility>

bool dfs(
    std::vector<std::vector<std::pair<int,int>>>& edges,
    std::vector<int>& d,
    std::vector<int>& result,
    std::vector<bool>& visited,
    const int edge_number,
    const int current
) {
    visited[current] = true;
    bool add_edge = false;
    for (auto& neightbour: edges[current]) {
        if (!visited[neightbour.first]) {
            if (dfs(edges, d, result, visited, neightbour.second, neightbour.first)) {
                add_edge = !add_edge;
            }
        }
    }
    if (d[current] == 1) {
        add_edge = !add_edge;
    }
    if (add_edge && edge_number >= 0) {
        result.push_back(edge_number);
    }
    return add_edge;
}

int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<int> d(n);
    std::vector<std::vector<std::pair<int, int>>> edges(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> d[i];
    }
    for (int i = 0; i < m; ++i) {
        int a,b;
        std::cin >> a >> b;
        --a;
        --b;
        edges[a].push_back(std::make_pair(b, i));
        edges[b].push_back(std::make_pair(a, i));
    }
    int start_vertex = 0;
    for (int i = 0; i < n; ++i) {
        if (d[i] == -1) {
            start_vertex = i;
            break;
        }
    }
    std::vector<int> result;
    std::vector<bool> visited(n, false);
    if (dfs(edges, d, result, visited, -1, start_vertex) && d[start_vertex] >= 0) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << result.size() << std::endl;
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i] + 1;
            if (i + 1 < result.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
