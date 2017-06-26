#include <iostream>
#include <vector>
#include <deque>

void split_row_col(const long long int vertex,
        long long int& row,
        long long int& col,
        const long long int m
) {
    row = vertex / m;
    col = vertex - row * m;
}

long long int join_row_col(
    const long long int row,
    const long long int col,
    const long long int m
) {
    return row * m + col;
}

std::vector<long long int> get_zero_reachable(
    const long long int vertex,
    const long long int n,
    const long long int m,
    std::vector<bool>& lighted
) {
    long long int row;
    long long int col;
    split_row_col(vertex, row, col, m);
    std::vector<long long int> zero_reachable;
    long long int upper = join_row_col(row - 1, col, m);
    long long int below = join_row_col(row + 1, col, m);
    long long int on_the_left = join_row_col(row, col - 1, m);
    long long int on_the_right = join_row_col(row, col + 1, m);
    if (row > 1 && lighted[upper]) {
        zero_reachable.push_back(upper);
    }
    if (row + 1 < n && lighted[below]) {
        zero_reachable.push_back(below);
    }
    if (col > 1 && lighted[on_the_left]) {
        zero_reachable.push_back(on_the_left);
    }
    if (col + 1 < m && lighted[on_the_right]) {
        zero_reachable.push_back(on_the_right);
    }
    return zero_reachable;
}

void push_all_from_row(
    std::vector<bool>& lighted,
    const long long int row,
    const long long int n,
    const long long int m,
    std::vector<long long int>& target_vector
) {
    if (row >= 0 && row < n) {
        for (long long int col = 0; col < m; ++col) {
            long long int new_vertex = join_row_col(row, col, m);
            if (lighted[new_vertex]) {
                target_vector.push_back(new_vertex);
            }
        }
    }
}

void push_all_from_col(
    std::vector<bool>& lighted,
    const long long int col,
    const long long int n,
    const long long int m,
    std::vector<long long int>& target_vector
) {
    if (col >= 0 && col < m) {
        for (long long int row = 0; row < n; ++row) {
            long long int new_vertex = join_row_col(row, col, m);
            if (lighted[new_vertex]) {
                target_vector.push_back(new_vertex);
            }
        }
    }
}

std::vector<long long int> get_one_reachable(
    const long long int vertex,
    const long long int n,
    const long long int m,
    std::vector<bool>& lighted
) {
    long long int row;
    long long int col;
    split_row_col(vertex, row, col, m);
    std::vector<long long int> one_reachable;
    push_all_from_row(lighted, row - 2, n, m, one_reachable);
    push_all_from_row(lighted, row - 1, n, m, one_reachable);
    push_all_from_row(lighted, row, n, m, one_reachable);
    push_all_from_row(lighted, row + 1, n, m, one_reachable);
    push_all_from_row(lighted, row + 2, n, m, one_reachable);
    push_all_from_col(lighted, col - 2, n, m, one_reachable);
    push_all_from_col(lighted, col - 1, n, m, one_reachable);
    push_all_from_col(lighted, col, n, m, one_reachable);
    push_all_from_col(lighted, col + 1, n, m, one_reachable);
    push_all_from_col(lighted, col + 2, n, m, one_reachable);
    if (row >= n - 2 || col >= n - 2) {
        one_reachable.push_back(n * m - 1);
    }
    return one_reachable;
}


int main() {
    long long int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<bool> lighted(n * m, false);
    for (long long int i = 0; i < k; ++i) {
        long long int r,c;
        std::cin >> r >> c;
        r -= 1;
        c -= 1;
        lighted[r * m + c] = true;
    }

    std::deque<long long int> q;
    std::vector<long long int> d(n * m, 2 * n * m);
    q.push_back(0);
    d[0] = 0;
    while (!q.empty()) {
        long long int v = q.front();
        q.pop_front();
        for (auto& to: get_zero_reachable(v, n, m, lighted)) {
            if (d[to] > d[v]) {
                d[to] = d[v];
                q.push_front(to);
            }
        }
        for (auto& to: get_one_reachable(v, n, m, lighted)) {
            if (d[to] > d[v] + 1) {
                d[to] = d[v] + 1;
                q.push_back(to);
            }
        }
    }
    std::cout << (d[n * m - 1] < 2 * n * m ? d[n * m - 1] : -1) << std::endl;
    return 0;
}
