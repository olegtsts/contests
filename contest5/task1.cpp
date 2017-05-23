#include <iostream>
#include <algorithm>

void process_test() {
    int k,x,y;
    std::cin >> k >> x >> y;
    int max_points = std::max(x, y);
    int min_points = std::min(x, y);

    if (max_points == min_points) {
        std::cout <<  2 + std::max(std::min(k - max_points - 2, k - min_points), 0) << std::endl;
    } else if (max_points == min_points + 1) {
        std::cout << 1 + std::max(std::min(k - max_points - 1, k - min_points), 0) << std::endl;
    } else {
        std::cout << std::max(std::min(k - max_points, k - min_points), 0) << std::endl;
    }

}

int main() {
    int k;
    std::cin >> k;
    for (size_t i = 0; i < k; ++i) {
        process_test();
    }
    return 0;
}
