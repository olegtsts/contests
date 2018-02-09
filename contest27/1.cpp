#include <iostream>

int main() {
    long long x,y;
    std::cin >> x >> y;

    if (y <= 0) {
        std::cout << "No\n";
        return 0;
    } else if (y == 1 && x != 0) {
        std::cout << "No\n";
        return 0;
    } else if (y == 1 && x == 0) {
        std::cout << "Yes\n";
        return 0;
    } else if (y > x + 1) {
        std::cout << "No\n";
        return 0;
    } else {
        if ((x + y) % 2 == 1) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
        return 0;
    }
    return 0;
}
