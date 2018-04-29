#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

bool IsPossibleToPosition(
    const std::vector<std::pair<long long int, long long int>>& c,
    long long int x1, long long int x2,
    long long int n,
    const bool was_there_swap
) {
    std::vector<bool> is_possible_to_place_after(n, false);
    for (long long int i = 0; i < n; ++i) {
        long long int how_much_needed = (x2 + c[i].first - 1) / c[i].first;
        if (n - i >= how_much_needed) {
            is_possible_to_place_after[i] = true;
        }
    }
    long long int max_possible_index = n;
    for (long long int i = n - 1; i >= 0; --i) {
        if (is_possible_to_place_after[i]) {
            max_possible_index = i;
            break;
        }
    }
    if (max_possible_index == n) {
        return false;
    }
    for (long long int i = 0; i < n; ++i) {
        long long int how_much_needed = (x1 + c[i].first - 1) / c[i].first;
        if (how_much_needed + i <= max_possible_index) {
            std::cout << "Yes\n";
            if (was_there_swap) {
                std::cout << n - max_possible_index << " " << how_much_needed <<  std::endl;
                for (long long int j = max_possible_index; j < n; ++j) {
                    std::cout << c[j].second + 1 << " ";
                }
                std::cout << std::endl;
                for (long long int j = i; j < i + how_much_needed; ++j) {
                    std::cout << c[j].second + 1 << " ";
                }
            } else {
                std::cout << how_much_needed << " " << n - max_possible_index << std::endl;
                for (long long int j = i; j < i + how_much_needed; ++j) {
                    std::cout << c[j].second + 1 << " ";
                }
                std::cout << std::endl;
                for (long long int j = max_possible_index; j < n; ++j) {
                    std::cout << c[j].second + 1 << " ";
                }
            }
            return true;
        }
    }
    return false;
}

int main() {
    long long int n;
    std::cin >> n;
    long long int x1, x2;
    std::cin >> x1 >> x2;
    std::vector<std::pair<long long int, long long int>> c(n);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> c[i].first;

        c[i].second = i;
    }
    std::sort(c.begin(), c.end());
    if (!(IsPossibleToPosition(c, x1, x2, n, false) || IsPossibleToPosition(c, x2, x1, n, true))) {
        std::cout << "No\n";
    }
    return 0;
}
