#include <cstdlib>
#include <iostream>

int main() {
    int n = 75000;
    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i) {
        long long int x1, x2, y1, a, b, y2;
        x1 = rand() % 200000;
        x2 = rand() % 200000;
        y1 = rand() % 1000000000;
        y2 = rand() % 1000000000;
        a = rand() % 10000;
        b = rand() % 10000;
        std::cout << x1 << " " << x2 << " " << y1 << " " << a << " " << b << " " << y2 << std::endl;
    }
    long long int m = 500000;
    std::cout << m << std::endl;
    for (int i = 0; i < m; ++i) {
        long long int l, r, x;
        l = rand() % n;
        r = rand() % n;
        x = rand() % 1000000000;
        std::cout << l + 1 << " " << r + 1 << " " << x << std::endl;
    }
    return 0;
}
