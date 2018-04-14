#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    long long int n;
    long long int m;
    std::cin >> n >> m;
    std::vector<long long int> numbers(n);
    std::vector<long long int> k(m);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
        --numbers[i];
    }

    long long int difference = 0;
    for (long long int i = 0; i < m; ++i) {
        std::cin >> k[i];
        difference -= k[i];
    }
    long long int to_fix = 0;
    std::vector<long long int> actual_counts(m, 0);
    long long int last_position = 0;
    for (long long int i = 0; i < n; ++i) {
        ++actual_counts[numbers[i]];
        ++difference;
        while (actual_counts[to_fix] >= k[to_fix] && to_fix < m) {
            ++to_fix;
        }
        if (to_fix == m) {
            last_position = i + 1;
            break;
        }
    }
    if (to_fix < m) {
        std::cout << -1 << std::endl;
        return 0;
    }
    long long int min_difference = difference;
    long long int first_position = 0;
    while (last_position <= n) {
        --actual_counts[numbers[first_position]];
        --difference;
        to_fix = numbers[first_position];
        ++first_position;
        while (last_position < n && actual_counts[to_fix] < k[to_fix]) {
            ++actual_counts[numbers[last_position++]];
            ++difference;
        }
        if (actual_counts[to_fix] >= k[to_fix]) {
            min_difference = std::min(min_difference, difference);
        } else {
            std::cout << min_difference << std::endl;
            return 0;
        }
    }
    std::cout << min_difference << std::endl;
    return 0;
}
