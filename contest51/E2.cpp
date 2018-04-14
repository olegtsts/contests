#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>

struct State {
    bool is_possible = false;
    long long int min_sum = std::numeric_limits<long long int>::max();
};

int main() {
    std::ios::sync_with_stdio(false);
    long long int n;
    long long int k;
    std::cin >> k >> n;
    std::vector<State> without_last(k + 1);
    std::vector<State> with_last(k + 1);
    without_last[0] = {true, 0};
    std::vector<long long int> times(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> times[i];
    }
    std::sort(times.begin(), times.end());
    std::vector<long long int> diffs(n - 1);
    for (int i = 0; i + 1 < n; ++i) {
        diffs[i] = times[i + 1] - times[i];
    }
    if (n - 1 > 3 * k + 1) {
        std::vector<long long int> new_diffs(diffs);
        std::sort(new_diffs.begin(), new_diffs.end());
        long long int border_element = new_diffs[3 * k + 1];
        bool is_prev_element_more_than_border = false;
        std::vector<long long int> diffs_replacement;
        for (auto& diff: diffs) {
            bool is_current_more_that_border = (diff > border_element);
            if (!(is_prev_element_more_than_border && is_current_more_that_border)) {
                diffs_replacement.push_back(diff);
            }
            is_prev_element_more_than_border = is_current_more_that_border;
        }
        diffs = std::move(diffs_replacement);
    }
    for (size_t i = 0; i < diffs.size(); ++i) {
        std::vector<State> new_without_last(k + 1);
        std::vector<State> new_with_last(k + 1);
        for (int j = 0; j <= k; ++j) {
            if (without_last[j].is_possible) {
                new_without_last[j].is_possible = true;
                new_without_last[j].min_sum = std::min(new_without_last[j].min_sum, without_last[j].min_sum);
            }
            if (with_last[j].is_possible) {
                new_without_last[j].is_possible = true;
                new_without_last[j].min_sum = std::min(new_without_last[j].min_sum, with_last[j].min_sum);
            }
            if (j > 0) {
                if (without_last[j - 1].is_possible) {
                    new_with_last[j].is_possible = true;
                    new_with_last[j].min_sum = std::min(new_with_last[j].min_sum, without_last[j - 1].min_sum + diffs[i]);
                }
            }
        }
        with_last = std::move(new_with_last);
        without_last = std::move(new_without_last);
    }
    long long int result = std::numeric_limits<long long int>::max();
    if (with_last[k].is_possible) {
        result = std::min(result, with_last[k].min_sum);
    }
    if (without_last[k].is_possible) {
        result = std::min(result, without_last[k].min_sum);
    }
    std::cout << result << std::endl;
    return 0;
}
