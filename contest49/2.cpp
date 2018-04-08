#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<long long int> a;
    bool non_zero_met = false;
    for (int i = 0; i < n; ++i) {
        long long int number;
        std::cin >> number;
        if (number == 0 && non_zero_met) {
            std::cout << -1 << std::endl;
            return 0;
        }
        if (number != 0) {
            non_zero_met = true;
            a.push_back(number);
        }
    }

    long long int result = 0;
    long long int current_multiplied = 0;
    std::vector<long long int> prefix_options;
    for (size_t i = 0; i + 1 < a.size(); ++i) {
        long long int current_value = a[i];
        long long int next_value = a[i + 1];
        int cur_power = 0;
        while (cur_power < current_multiplied && current_value <= next_value) {
            current_value *= 2;
            ++cur_power;
        }
        if (current_value <= next_value) {
            current_multiplied = 0;
        } else {
            current_multiplied = current_multiplied - cur_power;
            while (current_value > next_value) {
                next_value *= 2;
                ++current_multiplied;
            }
        }

        result += current_multiplied;
    }

    std::cout << result << std::endl;
    return 0;
}
