#include <iostream>
#include <algorithm>
#include <numeric>

int gcd(int a, int b) {
    while (b > 0) {
        a = a % b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    int n;
    std::cin >> n;
    for (int a = n / 2; a >= 1; --a) {
        int b = n - a;
        if (a < b && gcd(a, b) == 1) {
            std::cout << a << " " << b << std::endl;
            return 0;
        }
    }
}
