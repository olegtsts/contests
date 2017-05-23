#include <iostream>
#include <vector>

void do_test(
    std::vector<int>& cells
) {
    int n,m,k;
    std::cin >> n >> m >> k;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            int input_color;
            std::cin >> input_color;
            if (input_color == 0) {
                cells[i * m + j] = 0;
            } else {
                cells[i * m + j] = ((i + j) % k + 1);
            }
        }
    }
    for (size_t i = 0; i < n; ++i) {
        int sequent_without_lamps = 0;
        for (size_t j = 0; j < m; ++j) {
            if (cells[i * m + j] == 0) {
                sequent_without_lamps = 0;
            } else {
                ++sequent_without_lamps;
            }
            if (sequent_without_lamps > k) {
                std::cout << "NO" << std::endl;
                return;
            }
        }
    }

    for (size_t j = 0; j < m; ++j) {
        int sequent_without_lamps = 0;
        for (size_t i = 0; i < n; ++i) {
            if (cells[i * m + j] == 0) {
                sequent_without_lamps = 0;
            } else {
                ++sequent_without_lamps;
            }
            if (sequent_without_lamps > k) {
                std::cout << "NO" << std::endl;
                return;
            }
        }
    }

    std::cout << "YES" << std::endl;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            std::cout << cells[i * m + j];
            if (j + 1 < m) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    int tests;
    std::cin >> tests;
    std::vector<int> cells(10000);
    for (size_t i = 0; i < tests; ++i) {
        do_test(cells);
    }
    return 0;
}
