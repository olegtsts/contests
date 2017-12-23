#include <algorithm>
#include <iostream>

int main() {
    int v1,v2,v3,vm;
    std::cin >> v1 >> v2 >> v3 >> vm;
    int c = std::max(v3, vm);
    if (c > 2 * vm || c > 2 * v3) {
        std::cout << "-1\n";
        return 0;
    }
    int b = std::max(2 * vm + 1, std::max(c + 1, v2));
    if (b > 2 * v2) {
        std::cout << "-1\n";
        return 0;
    }
    int a = std::max(2 * vm + 1, std::max(b + 1, v1));
    if (b > 2 * v1) {
        std::cout << "-1\n";
        return 0;
    }
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    return 0;
}
