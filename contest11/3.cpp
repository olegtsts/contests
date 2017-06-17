#include <iostream>
#include <vector>

struct Move {
public:
    Move()
    {}

    Move(const bool is_row, const int index)
    : is_row(is_row)
    , index(index)
    {}

bool is_row;
int index;
};

std::vector<int> get_reverse_matrix(
    std::vector<int>& matrix,
    const int n,
    const int m
) {
    std::vector<int> new_matrix(n * m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            new_matrix[j * n + i] = matrix[i * m + j];
        }
    }
    return new_matrix;
}

void reverse_solution(
    std::vector<Move>& solution
) {
    for (auto& move: solution) {
        move.is_row = !move.is_row;
    }
}

std::vector<Move> solve(
    std::vector<int>& matrix,
    const int n,
    const int m
) {
    int min_index = -1;
    int min_value = 501;
    for (int j = 0; j < m; ++j) {
        if (min_value > matrix[j]) {
            min_value = matrix[j];
            min_index = j;
        }
    }
    std::vector<Move> solution;
    for (int j = 0; j < m; ++j) {
        int total_steps = matrix[j] - min_value;
        for (int steps = 0; steps < total_steps; ++steps) {
            solution.push_back(Move(false, j));
        }
        for (int i = 0; i < n; ++i) {
            matrix[i * m + j] -= total_steps;
        }
    }
    int first_col_actions = matrix[0] - min_value;
    for (int i = 0; i < n; ++i) {
        int total_steps = matrix[i * m];
        for (int steps = 0; steps < total_steps; ++steps) {
            solution.push_back(Move(true, i));
        }
        for (int j = 0; j < m; ++j) {
            matrix[i * m + j] -= total_steps;
        }
    }
    return solution;
}

bool is_matrix_zero(
    std::vector<int>& matrix
) {
    for (auto& el: matrix) {
        if (el != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<int> matrix(n * m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i * m + j];
        }
    }
    std::vector<Move> solution;
    if (n <= m) {
        solution = solve(matrix, n, m);
        if (!is_matrix_zero(matrix)) {
            std::cout << -1 << std::endl;
            return 0;
        }
    } else {
        auto new_matrix = get_reverse_matrix(matrix, n, m);
        solution = solve(new_matrix, m ,n);
        reverse_solution(solution);
        if (!is_matrix_zero(new_matrix)) {
            std::cout << -1 << std::endl;
            return 0;
        }
    }
    std::cout << solution.size() << std::endl;
    for (auto& move: solution) {
        if (move.is_row) {
            std::cout << "row ";
        } else {
            std::cout << "col ";
        }
        std::cout << move.index + 1 << std::endl;
    }
    return 0;
}
