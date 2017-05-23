#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long int n;
    std::cin >> n;
    std::vector<long long int> coords(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> coords[i];
    }
    std::sort(coords.begin(), coords.end());
    std::vector<long long int> powers_of_2(n + 1);
    const long long int modulo = 1000000007;
    powers_of_2[0] = 1;
    for (size_t i = 1; i < n + 1; ++i) {
        powers_of_2[i] = (powers_of_2[i - 1] * 2) % modulo;
    }
    long long int sum = 0;
    for (size_t i = 0; i + 1 < n; ++i) {
        long long int addon = (coords[i + 1] - coords[i]);
        addon %= modulo;
        addon *= (powers_of_2[i + 1] - 1);
        addon %= modulo;
        addon *= (powers_of_2[n - i - 1] - 1);
        addon %= modulo;
        sum += addon;
        sum %= modulo;
    }

    std::cout << sum << std::endl;

    return 0;
}

