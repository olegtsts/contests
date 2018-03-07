#include <cstdlib>
#include <iostream>

int main() {
    int n;
    int sum_of_modules = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int number;
        std::cin >> number;
        sum_of_modules += abs(number);
    }
    std::cout << sum_of_modules << std::endl;
    return 0;
}
