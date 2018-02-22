#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    long double R;
    long double x,y,x1,y1;
    std::cout << std::setprecision(10);

    std::cin >> R >> x >> y >> x1 >> y1;
    if ((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) >= R * R) {
        std::cout << x << " " << y << " " << R << std::endl;
    } else {
        double dist = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
        if (dist > 0) {
            std::cout << x - (x1 - x) * (R - dist) / dist / 2 << " " << y - (y1 - y) * (R - dist) / dist / 2 << " " << (R + dist) / 2 << std::endl;
        } else {
            std::cout << x + R / 2 << " " << y << " " << R / 2 << std::endl;
        }
    }
    return 0;
}
