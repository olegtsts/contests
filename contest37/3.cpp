#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::string s;
    std::cin >> s;
    int prefix_passed = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] <= 'a' + prefix_passed) {
            s[i] = 'a' + prefix_passed;
            ++prefix_passed;
            if (prefix_passed == 26) {
                break;
            }
        }
    }
    if (prefix_passed == 26) {
        std::cout << s << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
    return 0;
}
