#include <iostream>
#include <vector>
#include <utility>

std::pair<std::vector<int>, std::vector<int>> GetPermutationSchema(int n) {
    if (n == 4) {
        return {{1, 3, 0, 2}, {2, 0, 3, 1}};
    } else {
        std::vector<int> first_permutation;
        for (int i = 1; i < n; i += 2) {
            first_permutation.push_back(i);
        }
        for (int i = 0; i < n; i += 2) {
            first_permutation.push_back(i);
        }
        std::vector<int> second_permutation(n);
        for (int i = 0; i < n; i += 1) {
            second_permutation[(i + 1) % n] = first_permutation[i];
        }
        return {first_permutation, second_permutation};
    }
}

std::vector<std::vector<int>> GetField(int n, int m, const std::vector<std::vector<int>>& initial_field) {
    std::pair<std::vector<int>, std::vector<int>> permutations = GetPermutationSchema(m);
    std::vector<std::vector<int>> field(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i % 2 == 0) {
                field[i][j] = initial_field[i][permutations.first[j]];
            } else {
                field[i][j] = initial_field[i][permutations.second[j]];
            }
        }
    }
    return field;
}

void OutputField(const std::vector<std::vector<int>>& field) {
    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            std::cout << field[i][j];
            if (j + 1 < field[i].size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> TransposeField(const std::vector<std::vector<int>>& field) {
    std::vector<std::vector<int>> another_field(field[0].size(), std::vector<int>(field.size()));
    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            another_field[j][i] = field[i][j];
        }
    }
    return another_field;
}

std::vector<std::vector<int>> GenerateInitialField(int n, int m) {
    std::vector<std::vector<int>> initial_field(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            initial_field[i][j] = i * m + j + 1;
        }
    }
    return initial_field;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    if (n == 1 && m == 1) {
        std::cout << "YES\n1\n";
        return 0;
    }
    if (n == 3 && m == 3) {
        std::cout << "YES\n6 1 8\n7 5 3\n2 9 4\n";
        return 0;
    }

    if (n < 4 && m < 4) {
        std::cout << "NO\n";
        return 0;
    }
    std::cout << "YES\n";
    std::vector<std::vector<int>> initial_field = GenerateInitialField(n, m);
    if (m < 4) {
        OutputField(TransposeField(GetField(m, n, TransposeField(initial_field))));
    } else {
        OutputField(GetField(n, m, initial_field));
    }
    return 0;
}
