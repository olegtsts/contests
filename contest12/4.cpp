#include <iostream>
#include <vector>
#include <deque>

void add_edge(
    std::vector<std::vector<long long int> >& edges,
    std::vector<std::vector<long long int> >& zero_edges,
    const bool is_zero,
    const long long int source_row,
    const long long int source_col,
    const long long int target_row,
    const long long int target_col,
    const long long int n,
    const long long int m
) {
    long long int source = source_row * m + source_col;
    long long int target = target_row * m + target_col;
    if (is_zero) {
        zero_edges[source].push_back(target);
        zero_edges[target].push_back(source);
    } else {
        edges[source].push_back(target);
        edges[target].push_back(source);
    }
}

int main() {
    long long int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<long long int> > rows_cols(n);
    std::vector<std::vector<long long int> > cols_rows(m);
    std::vector<bool> lighted(n * m, false);
    for (long long int i = 0; i < k; ++i) {
        long long int r,c;
        std::cin >> r >> c;
        r -= 1;
        c -= 1;
        rows_cols[r].push_back(c);
        cols_rows[c].push_back(r);
        lighted[r * m + c] = true;
    }

    std::vector<std::vector<long long int> > edges(n * m);
    std::vector<std::vector<long long int> > zero_edges(n * m);
    for (long long int row = 0; row < n; ++row) {
        for (auto& col: rows_cols[row]) {
            for (auto& other_col: rows_cols[row]) {
                if (col + 1 < other_col) {
                    add_edge(edges, zero_edges, false, row, col, row, other_col, n, m);
                }
            }
            if (row + 1 < n) {
                for (auto& other_col: rows_cols[row + 1]) {
                    add_edge(edges, zero_edges, col == other_col, row, col, row + 1, other_col, n, m);
                }
            }
            if (row + 2 < n) {
                for (auto& other_col: rows_cols[row + 2]) {
                    add_edge(edges, zero_edges, false, row, col, row + 2, other_col, n, m);
                }
            }
        }
    }

    for (long long int col = 0; col < m; ++col) {
        for (auto& row: cols_rows[col]) {
            for (auto& other_row: cols_rows[col]) {
                if (row + 1 < other_row) {
                    add_edge(edges, zero_edges, false, row, col, other_row, col, n, m);
                }
            }
            if (col + 1 < m) {
                for (auto& other_row: cols_rows[col + 1]) {
                    add_edge(edges, zero_edges, row == other_row, row, col, other_row, col + 1, n, m);
                }
            }
            if (col + 2 < m) {
                for (auto& other_row: cols_rows[col + 2]) {
                    add_edge(edges, zero_edges, false, row, col, other_row, col + 2, n, m);
                }
            }
        }
    }
    if (!lighted[n * m - 1]) {
        for (auto& col: rows_cols[n - 1]) {
            add_edge(edges, zero_edges, false, n - 1, col, n - 1, m - 1, n, m);
        }
        for (auto& col: rows_cols[n - 2]) {
            add_edge(edges, zero_edges, false, n - 2, col, n - 1, m - 1, n, m);
        }
        for (auto& row: cols_rows[m - 1]) {
            add_edge(edges, zero_edges, false, row, m - 1, n - 1, m - 1, n, m);
        }
        for (auto& row: cols_rows[m - 2]) {
            add_edge(edges, zero_edges, false, row, m - 2, n - 1, m - 1, n, m);
        }
    }

    std::deque<long long int> q;
    std::vector<long long int> d(n * m, 2 * n * m);
    q.push_back(0);
    d[0] = 0;
    while (!q.empty()) {
        long long int v = q.front();
        q.pop_front();
        for (auto& to: edges[v]) {
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push_back(to);
            }
        }
        for (auto& to: zero_edges[v]) {
            if (d[to] > d[v]) {
                d[to] = d[v];
                q.push_front(to);
            }
        }
    }
    std::cout << (d[n * m - 1] < 2 * n * m ? d[n * m - 1] : -1) << std::endl;
    return 0;
}
