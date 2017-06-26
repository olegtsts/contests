#include <iostream>
#include <vector>
#include <deque>

int get_length(
    const long long int first_index,
    const long long int second_index,
    std::vector<std::pair<long long int, long long int> >& coords
) {
    long long int first_row = coords[first_index].first;
    long long int first_col = coords[first_index].second;
    long long int second_row = coords[second_index].first;
    long long int second_col = coords[second_index].second;
    int length = 1;
    if (first_row == second_row + 1 && first_col == second_col ||
            first_row == second_row - 1 && first_col == second_col ||
            first_col == second_col - 1 && first_row == second_row ||
            first_col == second_col + 1 && first_row == second_row) {
        length = 0;
    }
    return length;
}

int main() {
    long long int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<std::pair<long long int, long long int> > coords(k);
    std::vector<std::vector<long long int> > row_lights(n);
    std::vector<std::vector<long long int> > col_lights(m);
    long long int last_index = -1;
    for (long long int i = 0; i < k; ++i) {
        long long int r,c;
        std::cin >> r >> c;
        r -= 1;
        c -= 1;
        coords[i] = std::make_pair(r,c);
        row_lights[r].push_back(i);
        col_lights[c].push_back(i);
        if (r == n - 1 && c == m - 1) {
            last_index = i;
        }
    }

    long long int graph_size;
    if (last_index == -1) {
        graph_size = k + 1;
        last_index = k;
    } else {
        graph_size = k;
    }

    std::vector<std::vector<std::pair<long long int, int> > > graph(graph_size);
    for (long long int row = 0; row < n; ++row) {
        for (auto& first_index: row_lights[row]) {
            for (auto& new_row: {row - 2, row - 1, row, row + 1, row + 2}) {
                if (new_row >= 0 && new_row < n) {
                    for (auto& second_index: row_lights[new_row]) {
                        graph[first_index].push_back(std::make_pair(second_index, get_length(first_index, second_index, coords)));
                    }
                }
            }
        }
    }
    for (long long int col = 0; col < m; ++col) {
        for (auto& first_index: col_lights[col]) {
            for (auto& new_col: {col - 2, col - 1, col, col + 1, col + 2}) {
                if (new_col >= 0 && new_col < m) {
                    for (auto& second_index: col_lights[new_col]) {
                        graph[first_index].push_back(std::make_pair(second_index, get_length(first_index, second_index, coords)));
                    }
                }
            }
        }
    }

    if (last_index == k) {
        for (auto& row: {n - 2, n - 1}) {
            for (auto& index: row_lights[row]) {
                graph[index].push_back(std::make_pair(k, 1));
                graph[k].push_back(std::make_pair(index, 1));
            }
        }
        for (auto& col: {m - 2, m - 1}) {
            for (auto& index: col_lights[col]) {
                graph[index].push_back(std::make_pair(k, 1));
                graph[k].push_back(std::make_pair(index, 1));
            }
        }
    }


    int s = 0;
    std::vector<long long int> d(graph_size, 2 * n * m);
    d[0] = 0;
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
            }
        }
    }
    std::cout << (d[last_index] < 2 * n * m ? d[last_index] : -1) << std::endl;
    return 0;
}
