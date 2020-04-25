#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int GetMaxSumOfSubarray(const std::vector<int>& numbers) {
    int prefix_sum = 0;
    int min_prefix_sum = 0;
    int max_sum = std::numeric_limits<int>::min();
    for (int number : numbers) {
        prefix_sum += number;
        max_sum = std::max(max_sum, prefix_sum - min_prefix_sum);
        min_prefix_sum = std::min(min_prefix_sum, prefix_sum);
    }
    return max_sum;
}

int GetMaxSumOfSubsequence(const std::vector<int>& numbers) {
    int max_number = std::numeric_limits<int>::min();
    int sum_of_positives = 0;
    for (int number : numbers) {
        if (number > 0) {
            sum_of_positives += number;
        }
        max_number = std::max(max_number, number);
    }
    return sum_of_positives > 0 ? sum_of_positives : max_number;
}

void SolveTest() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    std::cout << GetMaxSumOfSubarray(numbers) << " " << GetMaxSumOfSubsequence(numbers) << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        SolveTest();
    }
    return 0;
}
