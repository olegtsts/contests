#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>

long long int SolveTest() {
    int n;
    std::cin >> n;
    std::vector<long long int> positives;
    std::vector<long long int> negatives;
    int zeros_count = 0;
    for (int i = 0; i < n; ++i) {
        int number;
        std::cin >> number;
        if (number > 0) {
            positives.push_back(number);
        } else if (number == 0) {
            ++zeros_count;
        } else {
            negatives.push_back(number);
        }
    }
    std::vector<long long int> chosen_numbers;
    std::sort(positives.begin(), positives.end());
    std::sort(negatives.begin(), negatives.end());
    std::copy(positives.rbegin(), positives.rbegin() + std::min(positives.size(), size_t(5)), std::back_inserter(chosen_numbers));
    std::copy(negatives.begin(), negatives.begin() + std::min(negatives.size(), size_t(5)), std::back_inserter(chosen_numbers));
    std::copy(negatives.rbegin(), negatives.rbegin() + std::min(static_cast<int>(negatives.size()) - 5, 5), std::back_inserter(chosen_numbers));
    for (int i = 0; i < std::min(zeros_count, 5); ++i) {
        chosen_numbers.push_back(0);
    }
    long long int max_product = std::numeric_limits<long long int>::min();
    for (size_t i1 = 0; i1 < chosen_numbers.size(); ++i1) {
        for (size_t i2 = i1 + 1; i2 < chosen_numbers.size(); ++i2) {
            for (size_t i3 = i2 + 1; i3 < chosen_numbers.size(); ++i3) {
                for (size_t i4 = i3 + 1; i4 < chosen_numbers.size(); ++i4) {
                    for (size_t i5 = i4 + 1; i5 < chosen_numbers.size(); ++i5) {
                        max_product = std::max(max_product, chosen_numbers[i1] * chosen_numbers[i2] * chosen_numbers[i3] * chosen_numbers[i4] * chosen_numbers[i5]);
                    }
                }
            }
        }
    }
    return max_product;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << SolveTest() << std::endl;
    }
    return 0;
}
