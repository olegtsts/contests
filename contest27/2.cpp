#include <iostream>

int main() {
    int n;
    std::cin >> n;
    long long int options_count = 0;
    for (int a = 1; a <= n; ++a) {
        for (int b = a; b <= n; ++b) {
            int c = a ^ b;
            if (c <= n && c >= b && c != a + b) {
                ++options_count;
            }
        }
    }
    std::cout << options_count << std::endl;
    return 0;
}
