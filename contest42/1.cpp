#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility>
#include <algorithm>

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};
int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<int> is_row_used(n, false);
    std::vector<int> is_col_used(m, false);
    std::unordered_set<std::pair<int, int>, pair_hash> points;
    std::vector<std::vector<int>> row_points(n);
    std::vector<std::vector<int>> col_points(m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char symbol;
            std::cin >> symbol;
            if (symbol == '#') {
                row_points[i].push_back(j);
                col_points[j].push_back(i);
                points.insert({i, j});
            }
        }
    }

    while (points.size() > 0) {
        auto first_point = *points.begin();
        for (int other_col: row_points[first_point.first]) {
            if (is_col_used[other_col]) {
                std::cout << "No\n";
                return 0;
            }
            is_col_used[other_col] = true;
        }
        for (int other_row: col_points[first_point.second]) {
            if (is_row_used[other_row]) {
                std::cout << "No\n";
                return 0;
            }
            is_row_used[other_row] = true;
        }
        for (int other_col: row_points[first_point.first]) {
            for (int other_row: col_points[first_point.second]) {
                if (points.count({other_row, other_col}) == 0) {
                    std::cout << "No\n";
                    return 0;
                }
                points.erase({other_row, other_col});
            }
        }
    }
    std::cout << "Yes\n";
    return 0;
}
