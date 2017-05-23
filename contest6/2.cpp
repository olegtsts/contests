#include <iostream>
#include <string>

int main () {
    std::string x,y;
    std::cin >> x >> y;
    std::string z(x.length(), '\0');
    for (size_t i = 0; i < x.length(); ++i) {
        if (x[i] >= y[i]) {
            z[i] = y[i];
        } else {
            std::cout << -1 << std::endl;
            return 0;
        }
    }
    std::cout << z << std::endl;
    return 0;
}
