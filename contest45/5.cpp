#include <iostream>

long long int GetCouplesCount(long long int n) {
    return (n + 1) / 2;
}

int main() {
    long long int n;
    std::cin >> n;
    long long int res = 0;
    long long int edge = 1;
    n -= 1;
    while (n > 0) {
        res += edge * GetCouplesCount(n);
        edge <<= 1;
        n >>= 1;
    }
    std::cout << res << std::endl;

    return 0;
}
