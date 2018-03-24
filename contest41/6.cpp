#include <iostream>
#include <vector>
#include <algorithm>

bool IsAnswerCorrect(
    const std::vector<long long int>& prefix_sums,
    const long long int middle_prefix_sum_index,
    const long long int answer,
    const long long int n,
    const long long int d,
    const long long int b
) {
    for (long long int i = answer; i <= n / 2; ++i) {
        long long int right_sum_border = std::max(std::min(i + (i + 1) * d, middle_prefix_sum_index), i);
        if (prefix_sums[right_sum_border + 1] - b * (i - answer) < b) {
            return false;
        }
    }
    for (long long int i = n - 1 - answer; i > n / 2; --i) {
        long long int left_sum_border = std::min(std::max(i - (n - i) * d, middle_prefix_sum_index), i);
        if (prefix_sums[n] - prefix_sums[left_sum_border] - b * (n - 1 - answer - i) < b) {
            return false;
        }
    }
    return true;
}

int main() {
    long long int n,d,b;
    std::cin >> n >> d >> b;
    std::vector<long long int> a(n);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<long long int> prefix_sums(n + 1, 0);
    long long int middle_prefix_sum_index = -1;
    for (long long int i = 0; i < n; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] + a[i];
        if (prefix_sums[i + 1] >= b * (n / 2 + 1) && middle_prefix_sum_index == -1) {
            middle_prefix_sum_index = i;
        }
    }
    long long int left_bound = 0;
    long long int right_bound = n;
    if (IsAnswerCorrect(prefix_sums, middle_prefix_sum_index, 0, n, d, b)) {
        std::cout << 0 << std::endl;
    } else {
        while (right_bound - left_bound >= 2) {
            long long int middle = (right_bound + left_bound) / 2;
            if (IsAnswerCorrect(prefix_sums, middle_prefix_sum_index, middle, n, d, b)) {
                right_bound = middle;
            } else {
                left_bound = middle;
            }
        }
        std::cout << right_bound << std::endl;
    }
    return 0;
}
