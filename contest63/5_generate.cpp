#include <cstdlib>
#include <iostream>

int main() {
    int n = 500;
    int k = 500;
    std::cout << n << " " << k << std::endl;
    for (int i = 0; i < n; ++i) {
        int a = rand() % 1000000000;
        int b = rand() % 1000000000;
        std::cout << a << " " << b << std::endl;
    }
    return 0;
}
