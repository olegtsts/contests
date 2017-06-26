#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> table(n * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0;j < n; ++j) {
            std::cin >> table[i * n + j];
        }
    }
    std::vector<bool> cached_row(100001, false);
    bool is_table_ok = true;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            cached_row[table[row * n + col]] = true;
        }
        for (int col = 0; col < n; ++col) {
            int target_value = table[row * n + col];
            if (target_value != 1) {
                bool can_be_represented = false;
                for (int check_row = 0; check_row < n; ++check_row) {
                    int first_part = table[check_row * n + col];
                    int second_part = target_value - first_part;
                    if (second_part >= 0 && cached_row[second_part]) {
                        can_be_represented = true;
                        break;
                    }
                }
                if (!can_be_represented) {
                    is_table_ok = false;
                    break;
                }
            }
        }
        for (int col = 0; col < n; ++col) {
            cached_row[table[row * n + col]] = false;
        }
        if (!is_table_ok) {
            break;
        }
    }
    if (is_table_ok) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
    return 0;
}
