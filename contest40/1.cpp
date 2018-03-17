#include <iostream>
#include <vector>
#include <utility>

int main() {
    int r,c;
    std::cin >> r >> c;
    std::vector<std::vector<char>> field(r, std::vector<char>(c, '.'));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            std::cin >> field[i][j];
            if (field[i][j] == '.') {
                field[i][j] = 'D';
            }
        }
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (field[i][j] == 'W') {
                for (std::pair<int, int> pair: std::vector<std::pair<int,int>>{{i - 1,  j}, {i + 1, j}, {i, j - 1}, {i, j + 1}}) {
                    if (pair.first >= 0 && pair.first < r && pair.second >= 0 && pair.second < c && field[pair.first][pair.second] == 'S') {
                        std::cout << "No\n";
                        return 0;
                    }
                }
            }
        }
    }
    std::cout << "Yes\n";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            std::cout << field[i][j];
        }
        std::cout << std::endl;
    }
    return 0;
}
