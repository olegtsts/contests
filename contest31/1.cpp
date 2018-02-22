#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int options = 0;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0 && n / i > 1) {
            ++options;
        }
    }
    std::cout << options << std::endl;
    return 0;
}
