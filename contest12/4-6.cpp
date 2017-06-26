#include <iostream>
#include <vector>
#include <unordered_map>

void add_edge(
    std::vector<std::vector<std::pair<int, int> > >& graph,
    const int first_index,
    const int second_index,
    const int length
) {
    graph[first_index].push_back(std::make_pair(second_index, length));
}

int main() {
    int n,m,k;
    std::cin >> n >> m >> k;
    long long int last_index = -1;
    std::vector<std::vector<std::pair<int, int> > > graph(n + m + k);
    std::unordered_map<long long int, int> cell_index;
    std::vector<std::pair<int, int> >coords(k);
    for (int i = 0; i < k; ++i) {
        int r,c;
        std::cin >> r >> c;
        r -= 1;
        c -= 1;
        if (r == n - 1 && c == m - 1) {
            last_index = n + m + i;
        }
        add_edge(graph, n + m + i, r, 1);
        add_edge(graph, r, n + m + i, 0);
        if (r + 1 < n) {
            add_edge(graph, n + m + i, r + 1, 1);
            add_edge(graph, r + 1, n + m + i, 0);
        }
        if (r >= 1) {
            add_edge(graph, n + m + i, r - 1, 1);
            add_edge(graph, r - 1, n + m + i, 0);
        }
        add_edge(graph, n + m + i, n + c, 1);
        if (c + 1 < m) {
            add_edge(graph, n + m + i, n + c + 1, 1);
            add_edge(graph, n + c + 1, n + m + i, 0);
        }
        if (c >= 1) {
            add_edge(graph, n + m + i, n + c - 1, 1);
            add_edge(graph, n + c - 1, n + m + i, 0);
        }
        cell_index[r * m + c] = i;
        coords[i] = std::make_pair(r, c);
    }
    for (int i = 0; i < k; ++i) {
        auto row = coords[i].first;
        auto col = coords[i].second;
        for (auto& new_coords: {std::make_pair(row - 1, col),
                std::make_pair(row + 1, col),
                std::make_pair(row, col - 1),
                std::make_pair(row, col + 1)}) {
            if (new_coords.first >= 0 && new_coords.first < n && new_coords.second >=0 && new_coords.second < m &&
                    cell_index.count(new_coords.first * m + new_coords.second) > 0) {
                auto new_index = cell_index[new_coords.first * m + new_coords.second];
                add_edge(graph, n + m + i, n + m + new_index, 0);
            }
        }
    }
    int graph_size = n + m + k;
    if (last_index == -1) {
        last_index = n + m + k;
        graph_size = last_index + 1;
        graph.push_back(std::vector<std::pair<int, int> >());
        for (auto& index: {n - 1, n + m - 1}) {
            add_edge(graph, index, last_index, 0);
        }
    }

    int s = n + m;
    std::vector<long long int> d(graph_size, 2 * n * m), p(graph_size, -1);
    d[s] = 0;
    std::vector<bool> u(graph_size);
    for (long long int i = 0; i < graph_size; ++i) {
        long long int v = -1;
        for (long long int j = 0; j < graph_size; ++j) {
            if (!u[j] && (v == -1 || d[j] < d[v])) {
                v = j;
            }
        }
        if (d[v] == 2 * n * m) {
            break;
        }
        u[v] = true;
        for (size_t j = 0; j < graph[v].size(); ++j) {
            long long int to = graph[v][j].first;
            int len = graph[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
//    int cur_index = last_index;
//    do {
//        std::cout << " " << cur_index;
//        cur_index = p[cur_index];
//    } while (cur_index >= 0);
//    std::cout << "\n";
    std::cout << (d[last_index] < 2 * n * m ? d[last_index] : -1) << std::endl;
    return 0;
}
