#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if (n <= 5) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << "1 2" << std::endl;
        std::cout << "1 3" << std::endl;
        std::cout << "1 4" << std::endl;
        for (int i = 5; i <= n; ++i) {
            std::cout << "4 " << i << std::endl;
        }
    }
    for (int i = 0; i + 1 < n; ++i) {
        std::cout << i + 1 << " " << i + 2 << std::endl;
    }
    return 0;
}
