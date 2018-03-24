#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Ratio {
    long long int numerator;
    long long int denominator;

    bool operator<(const Ratio& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    long double GetResult() const {
        return static_cast<long double>(numerator) / denominator;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    long long int u;
    std::cin >> n >> u;
    std::vector<long long int> E(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> E[i];
    }
    size_t first_index = 0;
    size_t second_index = 0;
    Ratio max_result{-1, 1};
    while (first_index < E.size()) {
        while (second_index < E.size() && E[second_index] - E[first_index] <= u) {
            ++second_index;
        }
        --second_index;
        if (first_index + 1 < second_index) {
            int third_index = first_index + 1;
            Ratio new_result{E[second_index] - E[third_index], E[second_index] - E[first_index]};
            max_result = std::max(max_result, new_result);
        }
        ++first_index;
    }
    std::cout << std::setprecision(10) << max_result.GetResult() << std::endl;
    return 0;
}
