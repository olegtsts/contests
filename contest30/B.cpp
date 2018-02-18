#include <iostream>
#include <vector>

struct NumberInfo {
    bool first_initialized = false;
    int first_index = -1;
    int second_index = -1;
    int first_position = -1;
    int second_position = -1;

    void AddIndexAndPosition(const int index, const int poistion) {
        if (first_initialized) {
            second_index = index;
            second_position = poistion;
        } else {
            first_index = index;
            first_position = poistion;
            first_initialized = true;
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> number_sets(2 * n, std::vector<int>(n, 0));
    std::vector<NumberInfo> numbers_info(n * n);
    std::vector<int> dialgonal_numbers(n);
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < n; ++j) {
            int number;
            std::cin >> number;
            --number;
            number_sets[i][j] = number;
            numbers_info[number].AddIndexAndPosition(i, j);
            if (numbers_info[number].first_position == numbers_info[number].second_position) {
                dialgonal_numbers[numbers_info[number].first_position] = number;
            }
        }
    }
    std::vector<int> rows_indices(n);
    rows_indices[0] = numbers_info[dialgonal_numbers[0]].first_index;
    auto& first_col = number_sets[numbers_info[dialgonal_numbers[0]].second_index];

    for (int i = 1; i < n; ++i) {
        int number = dialgonal_numbers[i];
        if (first_col[i] == number_sets[numbers_info[number].first_index][0]) {
            rows_indices[i] = numbers_info[number].first_index;
        } else {
            rows_indices[i] = numbers_info[number].second_index;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << number_sets[rows_indices[i]][j] + 1;
            if (i + 1 < n || j + 1 < n) {
                std::cout << " ";
            }
        }
    }
    std::cout << std::endl;
    return 0;
}
