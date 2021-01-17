#include <iostream>
#include <string>
#include <numeric>

int main() {
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        std::string s,t;
        std::cin >> s >> t;
        bool does_lcm_exist = true;
        std::string result_string;
        for (size_t j = 0; j < std::lcm(s.size(), t.size()); ++j) {
            if (s[j % s.size()] == t[j % t.size()]) {
                result_string.push_back(s[j % s.size()]);
            } else {
                does_lcm_exist = false;
                break;
            }
        }
        if (does_lcm_exist) {
            std::cout << result_string << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }
    return 0;
}
