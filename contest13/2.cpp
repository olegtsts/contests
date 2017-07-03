#include <iostream>
#include <vector>
#include <string>

int main() {
    int n,m;
    std::cin >> n >> m;
    std::string s, t;
    std::cin >> s >> t;
    int result = static_cast<int>(s.size());
    int min_shift = 0;
    for (size_t i = 0; i + s.size() < t.size() + 1; ++i) {
        int differences = 0;
        for (size_t j = 0; j < s.size(); ++j) {
            if (s[j] != t[i + j]) {
                ++differences;
            }
        }
        if (result > differences) {
            result = differences;
            min_shift = i;
        }
    }
    std::cout << result << std::endl;
    for (size_t j = 0; j < s.size(); ++j) {
        if (s[j] != t[min_shift + j]) {
            std::cout << j + 1;
            if (--result > 0) {
                std::cout << " ";
            }
        }
    }
    std::cout << std::endl;
    return 0;
}
