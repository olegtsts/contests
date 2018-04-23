#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    int n,k;
    std::cin >> n >> k;
    std::vector<std::vector<bool>> is_there_ship(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char ch;
            std::cin >> ch;
            if (ch == '.') {
                is_there_ship[i][j] = true;
            }
        }
    }
    std::vector<std::vector<int>> cells_counts(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i + k <= n) {
                bool is_there_whole_ship = true;
                for (int s = 0; s < k; ++s) {
                    if (!is_there_ship[i + s][j]) {
                        is_there_whole_ship = false;
                        break;
                    }
                }
                if (is_there_whole_ship) {
                    for (int s = 0; s < k; ++s) {
                        ++cells_counts[i + s][j];
                    }
                }
            }
            if (j + k <= n) {
                bool is_there_whole_ship = true;
                for (int s = 0; s < k; ++s) {
                    if (!is_there_ship[i][j + s]) {
                        is_there_whole_ship = false;
                        break;
                    }
                }
                if (is_there_whole_ship) {
                    for (int s = 0; s < k; ++s) {
                        ++cells_counts[i][j + s];
                    }
                }
            }
        }
    }
    int target_row,target_col;
    int max_count = std::numeric_limits<int>::min();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (max_count < cells_counts[i][j]) {
                max_count = cells_counts[i][j];
                target_row = i;
                target_col = j;
            }
        }
    }
    std::cout << target_row + 1 << " " << target_col + 1 << std::endl;
    return 0;
}
