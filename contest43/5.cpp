#include <limits>
#include <algorithm>
#include <iostream>
#include <vector>

enum class BackwardOption {ONE_SEQUENCE, TWO_SEQUENCE};

struct State {
    long long int min_steps = std::numeric_limits<long long int>::max();
    BackwardOption backward_option;

    bool operator<(const State& other) const {
        return min_steps < other.min_steps;
    }
};

long long int PerformStep(std::vector<long long int>& steps, std::vector<long long int>& p, const long long int index) {
    if (index + 1 < static_cast<long long int>(p.size()) && p[index] > 0 && p[index + 1] > 0) {
        steps.push_back(index);
        long long int min_number = std::min(p[index], p[index + 1]);
        p[index] -= min_number;
        p[index + 1] -= min_number;
        return min_number;
    }
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    long long int n;
    std::cin >> n;
    std::vector<long long int> p(n);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }
    std::vector<State> min_steps(n + 1);
    min_steps[0].min_steps = 0;
    min_steps[1].min_steps = 0;
    for (long long int i = 0; i < n; ++i) {
        if (i >= 1 && (i - 1 != 1 || p[0] == 0)) {
            min_steps[i + 1] = std::min(min_steps[i + 1], {min_steps[i - 1].min_steps + p[i], BackwardOption::ONE_SEQUENCE});
        }
        if (i >= 2 && (i - 2 != 1 || p[0] == 0)) {
            min_steps[i + 1] = std::min(min_steps[i + 1], {min_steps[i - 2].min_steps + std::max(p[i], p[i - 1]),  BackwardOption::TWO_SEQUENCE});
        }
    }
    long long int last_length;
    if (min_steps[n - 1] < min_steps[n]) {
        last_length = n - 1;
    } else {
        last_length = n;
    }
    std::vector<long long int> steps;
    long long int total_score = 0;
    while (last_length > 1) {
        if (min_steps[last_length].backward_option == BackwardOption::ONE_SEQUENCE) {
            total_score += PerformStep(steps, p, last_length - 2);
            total_score += PerformStep(steps, p, last_length - 1);
            last_length -= 2;
        } else {
            total_score += PerformStep(steps, p, last_length - 2);
            total_score += PerformStep(steps, p, last_length - 3);
            total_score += PerformStep(steps, p, last_length - 1);
            last_length -= 3;
        }
    }
    std::cout << steps.size() << std::endl;
    for (auto index: steps) {
        std::cout << index + 1 << std::endl;
    }
    return 0;
}
