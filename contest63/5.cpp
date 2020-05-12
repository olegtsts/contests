#include <iostream>
#include <vector>
#include <algorithm>

long long int GetSum(const std::vector<int>& vec, int mod) {
    long long int sum = 0;
    for (int value : vec) {
        sum += value;
    }
    return sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n,k;
    std::cin >> n >> k;
    std::vector<int> reds(n);
    std::vector<int> blues(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> reds[i] >> blues[i];
    }
    long long int reds_sum = GetSum(reds, k);
    long long int blues_sum = GetSum(blues, k);
    std::vector<bool> red_mods(k, false);
    red_mods[reds_sum % k] = true;
    for (int i = 0; i < n; ++i) {
        int min_red_diff = k - std::min(k, blues[i]);
        int max_red_diff = std::min(reds[i], k);
        std::vector<bool> new_red_mods = red_mods;
        for (int diff = min_red_diff; diff <= max_red_diff; ++diff) {
            for (int i = 0; i < k; ++i) {
                if (red_mods[i]) {
                    new_red_mods[(i - diff + k) % k] = true;
                }
            }
        }
        red_mods = std::move(new_red_mods);
    }
    for (int i = 0; i < k; ++i) {
        if (red_mods[i]) {
            int final_red_mod = i;
            int final_blue_mod = (reds_sum + blues_sum - i + k) % k;
            if (final_blue_mod + final_red_mod < k) {
                std::cout << (reds_sum + blues_sum) / k << std::endl;
                return 0;
            }
        }
    }
    std::cout << std::max((reds_sum + blues_sum) / k - 1ll, 0ll) << std::endl;
    return 0;
}
