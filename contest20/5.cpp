#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

struct SavedObject {
    int t;
    int d;
    int p;
    int i;
};

struct DynamicState {
    int max_points = 0;
    int prev_state_index = -1;
};

int Pack(const int t, const int k, const int n) {
    int index = 0;
    index += t;
    index *= (n + 1);
    index += k + 1;
    return index;
}

std::tuple<int, int> Unpack(int index, const int n) {
    int k = index % (n + 1) - 1;
    index /= (n + 1);
    int t = index;
    return std::make_tuple(t, k);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<SavedObject> saved_objects(n);
    for (int i = 0; i < n; ++i) {
        auto& saved_object = saved_objects[i];
        saved_object.i = i;
        std::cin >> saved_object.t >> saved_object.d >> saved_object.p;
    }
    std::sort(saved_objects.begin(), saved_objects.end(), [] (const SavedObject& a, const SavedObject& b) {return a.d < b.d;});
    std::vector<DynamicState> dynamic_state(2001 * (n + 1));
    DynamicState max_state;
    int max_last_index = -1;
    for (int t = 0; t <= 2000; ++t) {
        for (int k = -1; k + 1 < n; ++k) {
            auto& prev_state = dynamic_state[Pack(t, k, n)];
            for (int next_k = k + 1; next_k < n; ++next_k) {
                auto& next_object = saved_objects[next_k];
                if (t + next_object.t < next_object.d) {
                    auto& new_state = dynamic_state[Pack(t + next_object.t, next_k, n)];
                    if (new_state.max_points < prev_state.max_points + next_object.p) {
                        new_state.max_points = prev_state.max_points + next_object.p;
                        new_state.prev_state_index = Pack(t, k, n);
                    }
                    if (max_state.max_points < new_state.max_points) {
                        max_state = new_state;
                        max_last_index = next_k;
                    }
                }
            }
        }
    }
    std::cout << max_state.max_points << std::endl;
    if (max_last_index >= 0) {
        std::vector<int> results;
        results.push_back(saved_objects[max_last_index].i + 1);
        while (max_state.prev_state_index >= 0) {
            int t;
            int k;
            std::tie(t, k) = Unpack(max_state.prev_state_index, n);
            if (k == -1) {
                break;
            }
            results.push_back(saved_objects[k].i + 1);
            max_state.prev_state_index = dynamic_state[max_state.prev_state_index].prev_state_index;
        }
        std::cout << results.size() << std::endl;
        std::reverse(results.begin(), results.end());
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << results[i];
            if (i + 1 < results.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "0\n";
    }
    return 0;
}
