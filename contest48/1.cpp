#include <iostream>
#include <string>

int main() {
    std::string input_string;
    std::cin >> input_string;
    int a = 0;
    int b = 0;
    int c = 0;
    for (auto& symbol: input_string) {
        if (symbol == 'a') {
            ++a;
        } else if (symbol == 'b') {
            ++b;
        } else if (symbol == 'c') {
            ++c;
        } else {
            std::cout << "NO\n";
            return 0;
        }
    }
    for (size_t i = 0; i + 1 < input_string.size(); ++i) {
        if (input_string[i] > input_string[i + 1]) {
            std::cout << "NO\n";
            return 0;
        }
    }
    if (a != 0 && b != 0 && c != 0 && (a == c || b == c)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
