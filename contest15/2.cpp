#include <iostream>
#include <vector>

bool check_string(
    const char ch,
    const std::vector<std::vector<char>>& flag,
    const int i,
    const int m
) {
    for (int j = 0; j < m; ++j) {
        if (flag[i][j] != ch) {
            return false;
        }
    }
    return true;
}

bool is_flag_ok(
    const int n,
    const int m,
    const std::vector<std::vector<char>>& flag
) {
    if (n % 3 != 0) {
        return false;
    }
    char first_color = flag[0][0];
    char second_color = flag[n / 3][0];
    char third_color = flag[2 * n / 3][0];
    if (first_color == second_color || first_color == third_color || third_color == second_color) {
        return false;
    }
    for (int i = 0; i < n / 3; ++i) {
        if (!check_string(first_color, flag, i, m)) {
            return false;
        }
    }
    for (int i = n / 3; i < 2 * n / 3; ++i) {
        if (!check_string(second_color, flag, i, m)) {
            return false;
        }
    }
    for (int i = 2 * n / 3; i < n; ++i) {
        if (!check_string(third_color, flag, i, m)) {
            return false;
        }
    }
    return true;
}

int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<char>> flag(n);
    std::vector<std::vector<char>> inserse_flag(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char ch;
            std::cin >> ch;
            flag[i].push_back(ch);
            inserse_flag[j].push_back(ch);
        }
    }
    if (is_flag_ok(n, m, flag) || is_flag_ok(m, n, inserse_flag)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
