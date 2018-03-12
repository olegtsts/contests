#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>



int main() {
    int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> row_rid_lessons_remained_time(n, std::vector<int>(k + 1, std::numeric_limits<int>::max()));
    for (int i = 0; i < n; ++i) {
        std::vector<int> lesson_positions;
        for (int j = 0; j < m; ++j) {
            char symbol;
            std::cin >> symbol;
            if (symbol == '1') {
                lesson_positions.push_back(j);
            }
        }
        auto& rid_lessons_remained_time = row_rid_lessons_remained_time[i];
        for (int i = 0; i <= static_cast<int>(lesson_positions.size()) && i <= k; ++i) {
            // i -- count of first thrown
            for (int j = 0; j <= static_cast<int>(lesson_positions.size()) && j <= k - i; ++j) {
                // j - count of last thrown away
                int remained_time;
                if (static_cast<int>(lesson_positions.size()) - j - 1 >= i) {
                    remained_time = lesson_positions[lesson_positions.size() - j - 1] - lesson_positions[i] + 1;
                } else {
                    remained_time = 0;
                }
                rid_lessons_remained_time[i + j] = std::min(rid_lessons_remained_time[i + j], remained_time);
            }
        }
    }
    std::vector<int> first_rows_rid_lessons_min_remained_time(k + 1, std::numeric_limits<int>::max());
    first_rows_rid_lessons_min_remained_time[0] = 0;
    for (int i = 0; i < n; ++i) {
        std::vector<int> new_first_rows_rid_lessons_min_remained_time(k + 1, std::numeric_limits<int>::max());
        auto& rid_lessons_remained_time = row_rid_lessons_remained_time[i];
        for (int j = 0; j <= k; ++j) {
            int minimal_remained_time = std::numeric_limits<int>::max();
            for (int s = 0; s <= k; ++s) {
                if (j >= s && first_rows_rid_lessons_min_remained_time[j - s] < std::numeric_limits<int>::max()
                    && rid_lessons_remained_time[s] < std::numeric_limits<int>::max()
                ) {
                    int remained_time = first_rows_rid_lessons_min_remained_time[j - s] + rid_lessons_remained_time[s];
                    minimal_remained_time = std::min(remained_time, minimal_remained_time);
                }
            }
            new_first_rows_rid_lessons_min_remained_time[j] = minimal_remained_time;
        }
        first_rows_rid_lessons_min_remained_time = std::move(new_first_rows_rid_lessons_min_remained_time);
    }
    int minimal_remained_time = std::numeric_limits<int>::max();
    for (auto& remained_time : first_rows_rid_lessons_min_remained_time) {
        minimal_remained_time = std::min(minimal_remained_time, remained_time);
    }
    std::cout << minimal_remained_time << std::endl;
    return 0;
}
