#include <iostream>
#include <vector>
#include <optional>
#include <cassert>
#include <algorithm>

int GetBit(long long int number, int bit) {
    return (number >> bit) % 2;
}

void SetBit(long long int * number, int bit) {
    *number |= (1ll << bit);
}

std::vector<long long int> FindThreeNumbers(long long int exor, long long int esum) {
    std::vector<int> counters(64, 0);
    int passed_from_prev = 0;
    for (int i = 0; i < 62; ++i) {
        if (GetBit(exor, i) == 1) {
            counters[i] = 1;
        }
        if ((counters[i] + passed_from_prev + GetBit(esum, i)) % 2 == 1) {
            assert(i > 0);
            counters[i - 1] += 2;
            passed_from_prev += 1;
        }
        passed_from_prev = (counters[i] + passed_from_prev) / 2;
    }
    long long int a = 0;
    long long int b = 0;
    long long int c = 0;
    for (int i = 0; i < 62; ++i) {
        if (counters[i] >= 1) {
            SetBit(&a, i);
        }
        if (counters[i] >= 2) {
            SetBit(&b, i);
        }
        if (counters[i] >= 3) {
            SetBit(&c, i);
        }
    }
    std::vector<long long int> nonzero_numbers{a, b, c};
    nonzero_numbers.erase(std::remove(nonzero_numbers.begin(), nonzero_numbers.end(), 0ll), nonzero_numbers.end());
    return nonzero_numbers;
}

int main() {
    long long int expected_xor, expected_sum;
    std::cin >> expected_xor >> expected_sum;
    if (expected_xor > expected_sum || (expected_xor + expected_sum) % 2 == 1) {
        std::cout << -1 << std::endl;
    } else {
        std::vector<long long int> result = FindThreeNumbers(expected_xor, expected_sum);
        std::cout << result.size() << std::endl;
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i + 1 < result.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
