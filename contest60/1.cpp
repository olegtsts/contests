#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <utility>

enum class RowType {
    UNDEFINED = 0,
    FULL = 1,
    ONE = 2
};

std::vector<RowType> GetRowTypes(int number) {
    int rows = std::min(number, 30);
    std::vector<RowType> row_types(rows, RowType::ONE);
    if (number <= 30) {
        return row_types;
    }
    number -= 30;
    int reserve_ones = 0;
    for (int current_degree = 29; current_degree >= 1; --current_degree) {
        // invariant: number <= 2**(current_degree + 1) - 2
        // for current_degree = 29: 2**30 - 2 = 1073741822 > 1e9 >= number
        if (number >= pow(2, current_degree) - 1) {
            number -= pow(2, current_degree) - 1;
            row_types[current_degree] = RowType::FULL;
        }
        // After this, number <= 2**current_degree - 1
        if (number == pow(2, current_degree) - 1) {
            --number;
            ++reserve_ones;
        }
        // after this, number <= 2**current_degree - 2
    }
    // here invariant preserves: number <= 2**(0 + 1) - (2) = 0
    for (int i = 0; i < reserve_ones; ++i) {
        row_types.push_back(RowType::ONE);
    }
    // Estimate how many cells we used: <= 1 + 2 + .. + 30 + 29 = 30*31/2+29 = 494
    return row_types;
}

std::vector<std::pair<int, int>> GetPathByRowTypes(const std::vector<RowType>& row_types) {
    bool at_left = true;
    std::vector<std::pair<int, int>> result_path;
    for (int i = 0; i < static_cast<int>(row_types.size()); ++i) {
        if (row_types[i] == RowType::ONE) {
            result_path.push_back(std::make_pair(i + 1, at_left ? 1 : i + 1));
        } else if (row_types[i] == RowType::FULL) {
            if (at_left) {
                for (int j = 1; j <= i + 1; ++j) {
                    result_path.push_back(std::make_pair(i + 1, j));
                }
            } else {
                for (int j = i + 1; j >= 1; --j) {
                    result_path.push_back(std::make_pair(i + 1, j));
                }
            }
            at_left = !at_left;
        }
    }
    return result_path;
}

void ProcessTest() {
    int number;
    std::cin >> number;
    std::vector<RowType> row_types = GetRowTypes(number);
    std::vector<std::pair<int, int>> result_path = GetPathByRowTypes(row_types);
    for (const auto cur_pair : result_path) {
        std::cout << cur_pair.first << " " << cur_pair.second << std::endl;
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ":\n";
        ProcessTest();
    }
    return 0;
}
