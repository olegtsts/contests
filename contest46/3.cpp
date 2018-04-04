#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int GetOddDifferences(const std::vector<std::vector<int>>& board, const int n, int what_is_odd) {
    int differences_count = 0;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (board[row][col] != what_is_odd) {
                ++differences_count;
            }
            what_is_odd = 1 - what_is_odd;
        }
    }
    return differences_count;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<std::vector<std::vector<int>>> boards(4, std::vector<std::vector<int>>(n, std::vector<int>(n, 0)));

    for (int i = 0; i < 4; ++i) {
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                char symbol;
                std::cin >> symbol;
                boards[i][row][col] = symbol - '0';
            }
        }
    }
    int min_cells_to_fix = std::numeric_limits<int>::max();
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            // i and j are black-odd
            int s, m;
            s = -1;
            m = -1;
            for (int k = 0; k < 4; ++k) {
                if (k != i && k != j) {
                    if (s == -1) {
                        s = k;
                    } else {
                        m = k;
                    }
                }
            }
            //m and k are black-even
            min_cells_to_fix = std::min(min_cells_to_fix,
                                        GetOddDifferences(boards[i], n, 1)
                                        + GetOddDifferences(boards[j], n, 1)
                                        + GetOddDifferences(boards[s], n, 0)
                                        + GetOddDifferences(boards[m], n, 0));
        }
    }
    std::cout << min_cells_to_fix << std::endl;
    return 0;
}
