#include <iostream>
#include <vector>

int main() {
    int m;
    std::cin >> m;
    std::vector<int> s(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> s[i];
        if (s[i] % s[0] != 0) {
            std::cout << -1 << std::endl;
            return 0;
        }
    }
    std::cout << 2 * m << std::endl;
    for (int i = m - 1; i >= 0; --i) {
        std::cout << s[i] << " " << s[0];
        if (i > 0) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
