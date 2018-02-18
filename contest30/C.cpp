#include <iostream>

long long int MODULO = 1000000007;

long long int GetPower(long long int base, long long int input_power) {
    long long int x = 1;
    while (input_power > 0) {
        if (input_power % 2 == 0) {
            base *= base;
            base %= MODULO;
            input_power /= 2;
        } else {
            x *= base;
            x %= MODULO;
            input_power -= 1;
        }
    }
    return x;
}

int main() {
    long long int n;
    std::cin >> n;
    std::cout << GetPower(GetPower(n, n - 1), n - 1) << std::endl;
    return 0;
}
