#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

long long int GetResultFromBuffer(const std::vector<long long int>& buffer) {
    long long int sum_of_squares = 0;
    long long int sum = 0;
    for (auto& number: buffer) {
        sum += number;
        sum_of_squares += number * number;
    }
    return ((sum * sum) + sum_of_squares) / 2;
}

int main() {
    std::ios::sync_with_stdio(false);
    long long int n,x,k;
    std::cin >> n >> x >> k;
    std::vector<long long int> a(n, 0);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    if (k == 0) {
        std::sort(a.begin(), a.end());
        std::vector<long long int> buffer;
        long long int prev_x = -1;
        long long int prev_number = -1;
        long long int pairs_count = 0;
        for (auto& number: a) {
            if (number % x != 0) {
                long long int cur_x = number / x;
                if (prev_x != -1 && prev_x != cur_x) {
                    pairs_count += GetResultFromBuffer(buffer);
                    buffer.clear();
                }
                if (prev_number != number) {
                    buffer.push_back(0);
                }
                ++buffer.back();
                prev_number = number;
                prev_x = cur_x;
            }
        }
        if (buffer.size() > 0) {
            pairs_count += GetResultFromBuffer(buffer);
        }
        std::cout << pairs_count << std::endl;
        return 0;

//        std::unordered_map<long long int, long long int> div_results_count;
//        for (auto number: a) {
//            if (number % x != 0) {
//                long long int result = number / x;
//                if (div_results_count.count(result) == 0) {
//                    div_results_count[result] = 0;
//                }
//                ++div_results_count[result];
//            }
//        }
//        long long int pairs_count = 0;
//        for (auto& pair: div_results_count) {
//            long long int count_of_same_result = pair.second;
//            pairs_count += (count_of_same_result) * (count_of_same_result - 1) / 2 + count_of_same_result;
//        }
//        std::cout << pairs_count << std::endl;
//        return 0;
    } else {
        std::unordered_map<long long int, long long int> less_div_counts;
        std::unordered_map<long long int, long long int> not_more_div_counts;
        for (auto number: a) {
            long long int result = number / x;
            long long int result_for_less;
            long long int result_for_not_more;
            if (number % x == 0) {
                result_for_less = result - 1;
                result_for_not_more = result;
            } else {
                result_for_less = result;
                result_for_not_more = result;
            }
            if (less_div_counts.count(result_for_less) == 0) {
                less_div_counts[result_for_less] = 0;
            }
            ++less_div_counts[result_for_less];
            if (not_more_div_counts.count(result_for_not_more) == 0) {
                not_more_div_counts[result_for_not_more] = 0;
            }
            ++not_more_div_counts[result_for_not_more];
        }
        long long int pairs_count = 0;
        for (auto& pair: less_div_counts) {
            if (not_more_div_counts.count(pair.first + k)) {
                pairs_count += pair.second * not_more_div_counts[pair.first + k];
            }
        }
        std::cout << pairs_count << std::endl;
        return 0;
    }
}
