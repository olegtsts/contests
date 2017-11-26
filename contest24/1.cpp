#include <cstdlib>
#include <limits>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<size_t> a(n, 0);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    size_t min_distance = std::numeric_limits<size_t>::max();
    for (size_t j = 0; j < n; ++j) {
        size_t sum_of_angles = 0;
        for (size_t k = 0; k < n; ++k) {
            sum_of_angles += a[(j + k) % n];
            min_distance = std::min(min_distance, static_cast<size_t>(abs(360 - 2 * static_cast<int>(sum_of_angles))));
        }
    }
    std::cout << min_distance << std::endl;
    return 0;
}
