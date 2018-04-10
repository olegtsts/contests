#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

int main() {
    long long int n;
    std::cin >> n;
    std::vector<long long int> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    long long int min_crossed_out = std::numeric_limits<long long int>::max();
    for (long long int mask = 1; mask < (1ll << (digits.size())); ++mask) {
        long long int result_number = 0;
        bool are_there_leading_zeros = false;
        bool seen_first = false;
        long long int how_much_digits_crossed_out = 0;
        for (long long int pos = static_cast<long long int>(digits.size()) - 1; pos >= 0; --pos) {
            if (mask & (1ll << pos)) {
                result_number *= 10;
                result_number += digits[pos];
                if (!seen_first && digits[pos] == 0) {
                    are_there_leading_zeros = true;
                    break;
                }
                seen_first = true;
            } else {
                ++how_much_digits_crossed_out;
            }

        }
        if (!are_there_leading_zeros && static_cast<long long int>(sqrt(result_number)) * static_cast<long long int>(sqrt(result_number)) == result_number) {
            min_crossed_out = std::min(min_crossed_out, how_much_digits_crossed_out);
        }
    }
    if (min_crossed_out == std::numeric_limits<long long int>::max()) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << min_crossed_out << std::endl;
    }
    return 0;
}
