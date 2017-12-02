#include <iostream>

int main() {
    long long int k, p;
    std::cin >> k >> p;
    long long int result = 0;
    for (long long int i = 1; i <= k; ++i) {
        int number = i;
        int reverse_number = 0;
        int power_of_ten = 1;
        while (number > 0) {
            int digit = number % 10;
            reverse_number *= 10;
            reverse_number += digit;
            number /= 10;
            power_of_ten *= 10;
        }
        result += (i * power_of_ten) + reverse_number;
        result %= p;
    }
    std::cout << result << std::endl;
    return 0;
}
