#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

int main() {
    int n;
    std::cin >> n;
    std::vector<long long int> a(n);
    std::vector<std::pair<long long int, int>> b_pairs(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b_pairs[i].first;
        b_pairs[i].second = i;
    }
    std::sort(b_pairs.begin(), b_pairs.end());
    std::sort(a.begin(), a.end());
    std::vector<long long int> result(n, 0);
    for (int i = 0; i < n; ++i) {
        result[b_pairs[i].second] = a[n - 1 - i];
    }
    for (int i = 0; i < n; ++i) {
        std::cout << result[i];
        if (i + 1 < n) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
