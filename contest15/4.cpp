#include <iostream>
#include <vector>
#include <algorithm>

struct Powers {
    int two_power;
    int five_power;
};

int pack(const int five_power, const int k1, const int k) {
    return five_power * (k + 1) + k1;
}

int main() {
    int n,k;
    std::cin >> n >> k;
    std::vector<Powers> a(n);
    for (int i = 0;i < n; ++i) {
        long long int number;
        std::cin >> number;
        Powers powers{0, 0};
        while (number % 2 == 0) {
            ++powers.two_power;
            number /= 2;
        }
        while (number % 5 == 0) {
            ++powers.five_power;
            number /= 5;
        }
        a[i] = powers;
    }
    const int max_power = 27 * n;
    std::vector<int> prev_layer(max_power * (k + 1), -1);
    std::vector<int> layer(max_power * (k + 1), -1);
    prev_layer[pack(0, 0, k)] = 0;
    for (int i = 0; i < n; ++i) {
        for (int five_power = 0; five_power < max_power; ++five_power) {
            for (int j = 0; j < k + 1; ++j) {
                int max_two_power = prev_layer[pack(five_power, j, k)];
                if (j > 0 && five_power >= a[i].five_power) {
                    int prev_two_power = prev_layer[pack(five_power - a[i].five_power, j - 1, k)];
                    if (prev_two_power >= 0) {
                        int new_max_power = prev_two_power + a[i].two_power;
                        if (new_max_power > max_two_power) {
                            max_two_power = new_max_power;
                        }
                    }
                }
                layer[pack(five_power, j, k)] = max_two_power;
            }
        }
        std::swap(prev_layer, layer);
    }
    int max_round = 0;
    for (int i = 0; i < max_power; ++i) {
        int cur_round = std::min(i, prev_layer[pack(i, k, k)]);
        if (max_round < cur_round) {
            max_round = cur_round;
        }
    }
    std::cout << max_round << std::endl;
    return 0;
}
