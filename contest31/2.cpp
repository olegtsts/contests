#include <iostream>
#include <string>

void ProcessStep(int& x, int& y, const char symbol) {
    if (symbol == 'U') {
        ++y;
    } else {
        ++x;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::string input_string;
    std::cin >> input_string;
    int x = 0;
    int y = 0;
    ProcessStep(x, y, input_string[0]);
    bool is_below = x > y;
    int pay = 0;
    for (size_t i = 1; i < input_string.size(); ++i) {
        ProcessStep(x, y, input_string[i]);
        if (is_below && (x < y)) {
            ++pay;
            is_below = false;
        } else if (!is_below && (x > y)) {
            ++pay;
            is_below = true;
        }
    }
    std::cout << pay << std::endl;
    return 0;
}
