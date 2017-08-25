#include <iostream>
#include <set>
#include <utility>

struct SeenState {
    int not_overtake_signs_count = 0;
    std::set<std::pair<int, int>> speed_limits;
    int current_speed = 0;

    int PopUntil(const int target_speed, const bool with_equal) {
        int popped = 0;
        while (speed_limits.size() > 0) {
            auto first_pair = *speed_limits.begin();
            if ((first_pair.first >= target_speed && !with_equal) || (first_pair.first > target_speed && with_equal)) {
                break;
            }
            speed_limits.erase(first_pair);
            popped += first_pair.second;
        }
        return popped;
    }
};

int main() {
    int n;
    std::cin >> n;
    SeenState state;
    int errors = 0 ;
    for (int i = 0; i < n; ++i) {
        int t;
        std::cin >> t;
        if (t == 1) {
            std::cin >> state.current_speed;
            errors += state.PopUntil(state.current_speed, false);
        } else if (t == 2) {
            if (state.not_overtake_signs_count > 0) {
                errors += state.not_overtake_signs_count;
                state.not_overtake_signs_count = 0;
            }
        } else if (t == 3) {
            int speed;
            std::cin >> speed;
            int convered_signs = state.PopUntil(speed, true);
            state.speed_limits.insert(std::make_pair(speed, convered_signs + 1));
            errors += state.PopUntil(state.current_speed, false);
        } else if (t == 4) {
            state.not_overtake_signs_count = 0;
        } else if (t == 5) {
            state.speed_limits.clear();
        } else if (t == 6) {
            ++state.not_overtake_signs_count;
        }
    }
    std::cout << errors << std::endl;
    return 0;
}
