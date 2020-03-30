#include <iostream>

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        long long int x;
        std::cin >> x;
        if (x % 2 == 0) {
            std::cout << x / 2 << " " << x / 2 << std::endl;
        } else {
            long long int y = x - 1;
            long long int z = 1;
            while (y % 2 == 0) {
                y /= 2;
                z *= 2;
            }
            std::cout << y << " " << z << std::endl;
        }
    }
    return 0;
}
