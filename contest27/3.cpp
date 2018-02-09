#include <iostream>
#include <algorithm>
#include <numeric>

long long int gcd(long long int a, long long int b) {
    while (b > 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

long long int lcm(long long int a, long long int b) {
    return a * b / gcd(a,b);
}

int main() {
    long long int n;
    long long int k;
    std::cin >> n >> k;
    if (k >= 43) {
        std::cout << "No\n";
    } else {
        long long int fact = 1;
        for (long long int i = 2; i <= k; ++i) {
            fact = lcm(fact, i);
        }
        if ((n + 1) % fact == 0) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
    return 0;
}
