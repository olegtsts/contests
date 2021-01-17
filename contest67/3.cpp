#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, k;
        std::cin >> n >> k;
        for (int j = 1; j < 2 * k - n; ++j) {
            std::cout << j << " ";
        }
        for (int j = 2 * k - n; j <= k; ++j) {
            std::cout << 3 * k - n - j << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
