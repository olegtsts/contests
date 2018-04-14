#include <iostream>
#include <vector>

int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<int> numbers(n);
    std::vector<int> k(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
        --numbers[i];
    }
    int interval_length = 0;
    for (int j = 0; j < m; ++j) {
        std::cin >> k[j];
        interval_length += k[j];
    }

    std::vector<int> actual_counts(m, 0);
    for (int i = 0; i < interval_length; ++i) {
        ++actual_counts[numbers[i]];
    }

    if (k == actual_counts) {
        std::cout << "YES\n";
        return 0;
    }

    for (int i = interval_length; i < n; ++i) {
        --actual_counts[numbers[i - interval_length]];
        ++actual_counts[numbers[i]];
        if (k == actual_counts) {
            std::cout << "YES\n";
            return 0;
        }
    }
    std::cout << "NO\n";
    return 0;
}
