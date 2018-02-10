#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <tuple>

struct State {
    bool is_possible = false;
    long long int max_remained_manna = std::numeric_limits<long long int>::min();
};

size_t pack(const long long int counts_sum, const long long int bought, const long long int prefix) {
    return prefix * (counts_sum + 1) + bought;
}

std::tuple<long long int, long long int> unpack(const long long int packed, const long long int counts_sum) {
    long long int bought = packed % (counts_sum + 1);
    long long int prefix = packed / (counts_sum + 1);
    return std::make_tuple(bought, prefix);
}

int main() {
    std::ios::sync_with_stdio(false);
    long long int n, w,b,x;
    std::cin >> n >> w >> b >> x;
    std::vector<long long int> counts(n);
    std::vector<long long int> costs(n);
    long long int counts_sum = 0;
    for (long long int i = 0; i < n; ++i) {
        std::cin >> counts[i];
        counts_sum += counts[i];
    }
    for (long long int i = 0; i < n; ++i) {
        std::cin >> costs[i];
    }
    std::vector<State> states((n + 1) * (counts_sum + 1));
    states[pack(counts_sum, 0, 0)] = {true, w - x};
    long long int current_counts_sum = 0;
    for (long long int prefix = 1; prefix <= n; ++prefix) {
        current_counts_sum += counts[prefix - 1];
        for (long long int bought = 0; bought <= current_counts_sum; ++bought) {
            State& state = states[pack(counts_sum, bought, prefix)];
            for (long long int prev_bought = std::max(bought - counts[prefix - 1], 0ll); prev_bought <= bought; ++prev_bought) {
                long long int prev_prefix = prefix - 1;
                State prev_state = states[pack(counts_sum, prev_bought, prev_prefix)];
                if (prev_state.is_possible) {
                    long long int remained_manna = std::min(
                        prev_state.max_remained_manna + x, w + b * prev_bought) - costs[prefix - 1] * (bought - prev_bought);
                    if (remained_manna >= 0) {
                        state.is_possible = true;
                        if (state.max_remained_manna < remained_manna) {
                            state.max_remained_manna = remained_manna;
                        }
                    }
                }
            }
        }
    }
    long long int max_bought = 0;
    for (long long int bought = 0; bought <= counts_sum; ++bought) {
        State& state = states[pack(counts_sum, bought, n)];
        if (state.is_possible) {
            max_bought = bought;
        }
    }
    std::cout << max_bought << std::endl;
    return 0;
}
