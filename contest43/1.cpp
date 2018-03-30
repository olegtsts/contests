#include <iostream>
#include <vector>
#include <algorithm>

struct State {
    int max_subsequence = 0;
    std::vector<int> segments_start;

    void MergeWithState(const int position, const State& other, const bool add_new_segment, const bool add_last_digit) {
        int new_max_subsequence = other.max_subsequence + (add_last_digit ? 1 : 0);
        if (max_subsequence < new_max_subsequence) {
            max_subsequence = new_max_subsequence;
            segments_start = other.segments_start;
            if (add_new_segment) {
                segments_start.push_back(position);
            }
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    std::vector<std::vector<State>> prefix_segments_max_subsequence(n + 1, std::vector<State>(5, State{0, {}}));
    for (int i = 1; i <= n; ++i) {
        for (int k = 0; k <= 4; ++k) {
            auto& state = prefix_segments_max_subsequence[i][k];

            // Do not include last digit in sequence
            state.MergeWithState(i - 1, prefix_segments_max_subsequence[i - 1][k], false, false);

            if (k > 0 && ((numbers[i - 1] == 1 && k % 2 == 1) || (numbers[i - 1] == 2 && k % 2 == 0))) {
                // Include last digit
                state.MergeWithState(i - 1, prefix_segments_max_subsequence[i - 1][k - 1], true, true);
                state.MergeWithState(i - 1, prefix_segments_max_subsequence[i - 1][k], false, true);
            }
        }
    }
    int max_subsequence = 0;
    for (int k = 0; k <= 4; ++k) {
        max_subsequence = std::max(max_subsequence, prefix_segments_max_subsequence[n][k].max_subsequence);
    }
    std::cout << max_subsequence << std::endl;
    return 0;
}
