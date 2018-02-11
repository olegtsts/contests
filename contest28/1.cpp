#include <iostream>

int main() {
    int h,m;
    std::cin >> h >> m;
    h = 12 - h;
    m = 60 - m;
    h %= 12;
    m %= 60;
    std::cout << h << " " << m << std::endl;
    return 0;
}
