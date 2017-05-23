#include <iostream>

int main () {
    long long int n;
    std::cin >> n;
    for (long long int i = 1; i < n + 2; ++i) {
        if (n % i != 0) {
            std::cout << i << std::endl;
            return 0;
        }
    }
    return 0;
}
