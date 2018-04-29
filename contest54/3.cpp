#include <iostream>
#include <vector>

using INT = long long int;

int main() {
    INT n;
    std::cin >> n;
    std::vector<INT> b(n);
    for (INT i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    std::vector<std::vector<long long int>> leading_bit_numbers(60);
    for (auto number: b) {
        INT leading_bit;
        for (INT bit = 59; bit >= 0; --bit) {
            if (number & (1ll << bit)) {
                leading_bit = bit;
                break;
            }
        }
        leading_bit_numbers[leading_bit].push_back(number);
    }
    INT total_xor = 0;
    INT total_numbers = n;
    std::vector<INT> result_vector;
    while (total_numbers > 0) {
        bool is_possible = false;
        for (INT bit = 0; bit < 60; ++bit) {
            if ((total_xor & (1ll << bit)) == 0 && leading_bit_numbers[bit].size()) {
                is_possible = true;
                --total_numbers;
                result_vector.push_back(leading_bit_numbers[bit].back());
                total_xor ^= result_vector.back();
                leading_bit_numbers[bit].pop_back();
                break;
            }
        }
        if (!is_possible) {
            std::cout << "No\n";
            return 0;
        }
    }
    std::cout << "Yes\n";
    for (auto number: result_vector) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
    return 0;
}
