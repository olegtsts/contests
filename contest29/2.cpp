#include <algorithm>
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int max_time = 0;
    for (int i = 0; i < n; ++i) {
        int pos;
        std::cin >> pos;
        max_time = std::max(max_time, std::min(pos - 1, 1000000 - pos));
    }
    std::cout << max_time << std::endl;
    return 0;
}
