#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    long long int x, d;
    std::cin >> x >> d;
    std::vector<long long int> numbers;
    long long int current_number = 1;
    while (x > 0) {
        long long int deg_of_two = 1;
        int power_of_two = 0;
        while (deg_of_two <= x + 1) {
            deg_of_two <<= 1;
            ++power_of_two;
        }
        deg_of_two >>= 1;
        --power_of_two;
        for (int i = 0; i < power_of_two; ++i) {
            numbers.push_back(current_number);
        }
        current_number += d + 1;
        x -= (deg_of_two - 1);
    }
    std::cout << numbers.size() << std::endl;
    for (auto& number: numbers) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    return 0;
}
