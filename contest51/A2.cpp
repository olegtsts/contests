#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    int m,n;
    std::cin >> n >> m;
    std::vector<std::string> first_board(n, std::string(m, '\0'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> first_board[i][j];
        }
    }
    std::vector<std::string> second_board(m, std::string(n, '\0'));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> second_board[i][j];
        }
    }

    std::unordered_map<std::string, size_t> string_index;
    for (int i = 0; i <= n - m; ++i) {
        std::string whole_string;
        for (int j = 0; j < m; ++j) {
            whole_string += first_board[i + j];
        }
        string_index[whole_string] = i;
    }
    for (int i = 0; i <= n - m; ++i) {
        std::string whole_string;
        for (int j = 0; j < m; ++j) {
            whole_string += second_board[j].substr(i, m);
        }
        if (string_index.count(whole_string)) {
            std::cout << string_index[whole_string] + 1 << " " << i + 1 << std::endl;
            return 0;
        }
    }
    return 0;
}
