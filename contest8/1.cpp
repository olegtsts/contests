#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long int n,k;
    std::cin >> n >> k;
    std::vector<long long int> a(n);
    long long int prev_remainder = -1;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
        long long int remainder = (a[i] % k);
        if (prev_remainder >= 0 && prev_remainder != remainder) {
            std::cout << -1 << std::endl;
            return 0;
        }
        prev_remainder = remainder;
    }
    long long int min = *(std::min_element(a.begin(), a.end()));
    long long int steps = 0;
    for (size_t i = 0; i < n; ++i) {
        steps += (a[i] - min) / k;
    }
    std::cout << steps << std::endl;
    return 0;
}
