#include <algorithm>
#include <iostream>

int main() {
    int n, k;
    std::cin >> n >> k;
    if (n == k) {
        std::cout << "0 0\n";
    } else if (k == 0) {
        std::cout << "0 0\n";
    } else {
        std::cout << 1 << " " << std::min(n - k, 2 * k) << std::endl;
    }
    return 0;
}
