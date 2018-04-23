#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    long long int n,k,m,d;
    std::cin >> n >> k >> m >> d;
    long long int max_result = 0;

    std::vector<long long int> to_try;
    for (long long int y = 1; y <= d + 10; ++y) {
        if (y - 1 <= (n - 1) / k) {
            to_try.push_back(n / ((y - 1) * k + 1));
        }
    }
    to_try.push_back(4);
    to_try.push_back(m);
    for (auto x: to_try) {
        if (x <= m && ((k <= n / d && x >= n / (k * d + 1) + 1) || (k > n / d && x >= 1))) {
            long long int s = 1 + (n - x) / x / k;
            max_result = std::max(max_result, s * x);
        }
    }
    std::cout << max_result << std::endl;
    return 0;
}
