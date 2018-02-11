#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::string input_string;
    std::cin >> input_string;
    std::string min_string(1, '{');
    for (size_t i = 0; i + 1 < input_string.size(); ++i) {
        if (input_string[i] == input_string[i + 1]) {
            std::string cur_string = std::string(1, input_string[i]) + std::string(1, input_string[i + 1]);
            if (cur_string < min_string) {
                min_string = cur_string;
            }
        }
    }
    if (min_string[0] != '{') {
        std::cout << min_string << std::endl;
        return 0;
    }
    min_string = std::string(1, '{');
    for (size_t i = 0; i + 2 < input_string.size(); ++i) {
        if (input_string[i] == input_string[i + 2]) {
            std::string cur_string = std::string(1, input_string[i]) + std::string(1, input_string[i + 1]) + std::string(1, input_string[i + 2]);
            if (cur_string < min_string) {
                min_string = cur_string;
            }
        }
    }
    if (min_string[0] == '{') {
        std::cout << -1 << std::endl;
    } else {
        std::cout << min_string << std::endl;
    }
    return 0;
}
