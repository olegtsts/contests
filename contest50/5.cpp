#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int n;
    std::cin >> n;
    long long int result = 0;
    std::vector<long long int> x_p;
    std::vector<long long int> x_b;
    std::vector<long long int> x_r;

    for (int i = 0; i < n; ++i) {
        long long int x;
        char c;
        std::cin >> x >> c;
        if (c == 'B') {
            x_b.push_back(x);
        } else if (c == 'R') {
            x_r.push_back(x);
        } else {
            x_p.push_back(x);
        }
    }
    for (size_t i = 0; i + 1 < x_p.size(); ++i) {
        result += x_p[i + 1] - x_p[i];
    }
    for (size_t i = 0; i + 1 < x_p.size(); ++i) {
        long long int simple_addon = x_p[i + 1] - x_p[i];
        long long int alternative_addon = 0;
        for(auto x_vec_ref: {std::ref(x_r), std::ref(x_b)}) {
            auto& x_vec = x_vec_ref.get();
            auto lower = std::lower_bound(x_vec.begin(), x_vec.end(), x_p[i]);
            auto upper = std::lower_bound(x_vec.begin(), x_vec.end(), x_p[i + 1]);
            auto prev_x = x_p[i];
            long long int max_to_remove = 0;
            for (auto it = lower; it != upper; ++it) {
                max_to_remove = std::max(max_to_remove, *it - prev_x);
                prev_x = *it;
            }
            max_to_remove = std::max(max_to_remove, x_p[i + 1] - prev_x);
            alternative_addon += x_p[i + 1] - x_p[i] - max_to_remove;
        }
        result += std::min(simple_addon, alternative_addon);
    }
    if (x_p.size() > 0) {
        for(auto x_vec_ref: {std::ref(x_r), std::ref(x_b)}) {
            auto& x_vec = x_vec_ref.get();

            if (x_vec.size()) {
                if (x_vec[0] < x_p[0]) {
                    result += x_p[0] - x_vec[0];
                }
                if (x_vec.back() > x_p.back()) {
                    result += x_vec.back() - x_p.back();
                }
            }
        }
    } else {
        for(auto x_vec_ref: {std::ref(x_r), std::ref(x_b)}) {
            auto& x_vec = x_vec_ref.get();

            if (x_vec.size()) {
                result += x_vec.back() - x_vec[0];
            }
        }
    }
    std::cout << result << std::endl;
    return 0;
}
