#include <iostream>
#include <vector>
#include <algorithm>

size_t Pack(const int segments, const int last_segment_value, const int p) {
    size_t packed = 0;
    packed += segments;
    packed *= p;
    packed += last_segment_value;
    return packed;
}

struct State {
    bool is_possible = false;
    int max_score = 0;
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    int k;
    int p;
    std::cin >> n >> k >> p;
    std::vector<State> states((k + 1) * p, State{});
    states[Pack(0, 0, p)] = {true, 0};
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    for (int prefix = 0; prefix < n; ++prefix) {
//        std::cout << "Considering number " << prefix << std::endl;
        int current_number = numbers[prefix];
        std::vector<State> new_states((k + 1) * p, State{});
        for (int segments = 0; segments <= k; ++segments) {
            for (int last_segment_value = 0; last_segment_value < p; ++last_segment_value) {
                State& cur_state = states[Pack(segments, last_segment_value, p)];
                if (cur_state.is_possible) {
                    if (segments < k) {
                        State& future_state = new_states[Pack(segments + 1, current_number % p, p)];
                        future_state.is_possible = true;
                        future_state.max_score = std::max(future_state.max_score, cur_state.max_score + (current_number % p));
//                        std::cout << "From(" << segments << ", " << last_segment_value << ") to (" << segments + 1 << ", " << current_number % p << ") new_value " << future_state.max_score << std::endl;
                    }
                    if (segments > 0) {
                        State& future_state = new_states[Pack(segments, (last_segment_value + current_number) % p, p)];
                        future_state.is_possible = true;
                        future_state.max_score = std::max(future_state.max_score, cur_state.max_score + (last_segment_value + current_number) % p - last_segment_value);
//                        std::cout << "From(" << segments << ", " << last_segment_value << ") to (" << segments  << ", " << (last_segment_value + current_number) % p  << ") new_value " << future_state.max_score << std::endl;
                    }
                }
            }
        }
        states = std::move(new_states);
    }
    int max_score = 0;
    for (int last_segment_value = 0; last_segment_value < p; ++last_segment_value) {
        State& state = states[Pack(k, last_segment_value, p)];
        if (state.is_possible) {
            max_score = std::max(max_score, state.max_score);
        }
    }
    std::cout << max_score << std::endl;
    return 0;
}
