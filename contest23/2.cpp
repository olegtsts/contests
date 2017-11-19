#include <iostream>

long long int MODULO = 1000000007;

long long int GetPower(long long int base, long long int degree){
    long long int x = 1;
    while (degree > 0) {
        if (degree % 2 == 0) {
            base *= base;
            degree /= 2;
            base %= MODULO;
        } else {
            x *= base;
            --degree;
            x %= MODULO;
        }
    }
    return x;
}

int main() {
    long long int n,m,k;
    std::cin >> n >> m >> k;
    if (n % 2 != m % 2 && k == -1) {
        std::cout << 0 << std::endl;
        return 0;
    }
    std::cout << GetPower(GetPower(2, n - 1), m - 1) << std::endl;
    return 0;
}
