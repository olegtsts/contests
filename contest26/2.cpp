#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<char>> field(9, std::vector<char>(9, '.'));
    std::vector<std::vector<size_t>> filled_outer(3, std::vector<size_t>(3, 0));
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0;j < 9; ++j) {
            std::cin >> field[i][j];
            if (field[i][j] != '.') {
                ++filled_outer[i / 3][j / 3];
            }
        }
    }
    size_t prev_i, prev_j;
    std::cin >> prev_i >> prev_j;
    size_t macro_i = (prev_i - 1) % 3;
    size_t macro_j = (prev_j - 1) % 3;
    if (filled_outer[macro_i][macro_j] == 9) {
        for (size_t i = 0; i < 9; ++i) {
            for (size_t j = 0; j < 9; ++j) {
                if (field[i][j] == '.') {
                    field[i][j] = '!';
                }
            }
        }
    } else {
        for (size_t i = 0; i < 3; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                size_t cur_i = macro_i * 3 + i;
                size_t cur_j = macro_j * 3 + j;
                if (field[cur_i][cur_j] == '.') {
                    field[cur_i][cur_j] = '!';
                }
            }
        }
    }
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            std::cout << field[i][j];
            if ((j + 1) % 3 == 0) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
        if ((i + 1) % 3 == 0) {
            std::cout << std::endl;
        }
    }
    return 0;
}
