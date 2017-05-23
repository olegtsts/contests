#include <iostream>

int get_digits_count(int number) {
    size_t result = 0;
    while (number) {
        number &= number - 1;
        ++result;
    }
    return result;
}

int main() {
    int t;
    std::cin >> t;
    for (size_t i = 0; i < t; ++i) {
        long long int n;
        std::cin >> n;
        long long int multiplied = n;
        long long int mult = 1;
        for (size_t j = 0; j < 50; ++j) {
            if (mult == get_digits_count(multiplied)) {


    return 0;
}
