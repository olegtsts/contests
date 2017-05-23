#include <iostream>
#include <vector>
#include <algorithm>

struct Level {
    long long int a;
    long long int b;
    long long int x;

    Level()
    : a(0)
    , b(0)
    , x(0)
    {}

    Level(long long int a, long long int b, long long int x)
    : a(a)
    , b(b)
    , x(x)
    {}

    bool operator<(const Level& other) const {
        return (a - b) * other.x < (other.a - other.b) * x;
    }
};

void do_test() {
    int n;
    std::cin >> n;

    std::vector<Level> levels;
    for (size_t i = 0; i < n; ++i) {
        long long int a,b,x;
        std::cin >> a >> b >>  x;
        levels.push_back(Level(a, b, x));
    }
    std::sort(levels.begin(), levels.end());
    double result_expectation = 0;
    long long int prob_sum = 10000000;
    for (size_t i = 0; i < n; ++i) {
        result_expectation += levels[i].a * prob_sum;
        prob_sum -= levels[i].x;
    }
    prob_sum = 10000000;
    for (size_t i = 0; i < n; ++i) {
        prob_sum -= levels[n - i - 1].x;
        result_expectation += levels[n - i - 1].b * prob_sum;
    }
    std::cout << double(result_expectation) / 1e7 << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    for (size_t i = 0; i < t; ++i) {
        do_test();
    }
    return 0;
}
