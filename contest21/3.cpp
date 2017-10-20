#include <iostream>
#include <vector>

int main() {
    int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> field(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> field[i][j];
        }
    }
    int minimum_changed = 0;
    int max_points = 0;
    for (int j = 0; j < m; ++j) {
        int it_first = 0;
        int it_last = 0;
        int ones_counter = 0;
        int max_ones_counter = 0;
        int number_of_ones_met = 0;
        int local_minimum_changed = 0;
        while (it_first < n) {
            while (it_last < n && it_last - it_first < k) {
                if (field[it_last][j] == 1) {
                    ++ones_counter;
                }
                ++it_last;
            }
            if (field[it_first][j] == 1) {
                if (ones_counter > max_ones_counter) {
                    max_ones_counter = ones_counter;
                    local_minimum_changed = number_of_ones_met;
                }
                ++number_of_ones_met;
            }
            if (field[it_first][j] == 1) {
                --ones_counter;
            }
            ++it_first;
        }
        minimum_changed += local_minimum_changed;
        max_points += max_ones_counter;
    }
    std::cout << max_points << " " << minimum_changed << std::endl;
    return 0;
}
