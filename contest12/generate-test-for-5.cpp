#include <iostream>

int main() {
    long long int a = 999999999999999990ul;
    std::cout << 100 << " " << a - 9 << std::endl;
    for (long long int i = 0; i < 100; ++i) {
        std::cout << a / 99 * i << " " << a / 99 * (i + 1) << " " << 15 << std::endl;
    }
    return 0;
}
