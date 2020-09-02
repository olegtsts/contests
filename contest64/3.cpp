#include <iostream>
#include <vector>
#include <algorithm>

struct Flower {
    long long int a;
    long long int b;
};

struct PrefixStat {
    long long int a;
    long long int count;
    long long int sum;

    bool operator<(const PrefixStat& other) const {
        return a < other.a;
    }
};

void SolveTest() {
    long long int n;
    int m;
    std::cin >> n >> m;
    std::vector<Flower> flowers(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> flowers[i].a >> flowers[i].b;
    }
    std::sort(flowers.begin(), flowers.end(), [](const Flower& first, const Flower& second) {
        return first.a > second.a;
    });
    std::vector<PrefixStat> prefix_stats(m);
    PrefixStat stat{0, 0, 0};
    for (int i = 0; i < m; ++i) {
        stat.a = flowers[i].a;
        if (stat.count < n) {
            stat.count += 1;
            stat.sum += flowers[i].a;
        }
        prefix_stats[i] = stat;
    }
    std::reverse(prefix_stats.begin(), prefix_stats.end());
    long long int max_sum = 0;
    for (int i = 0; i < m; ++i) {
        auto it = std::upper_bound(prefix_stats.begin(), prefix_stats.end(), PrefixStat{flowers[i].b, 0, 0});
        PrefixStat stat;
        if (it == prefix_stats.end()) {
            stat = {0, 0, 0};
        } else {
            stat = *it;
        }
        long long int sum = stat.sum;
        long long int remaining_flowers = n - stat.count;
        if (remaining_flowers > 0 && flowers[i].a <= flowers[i].b) {
            sum += flowers[i].a;
            --remaining_flowers;
        }
        sum += remaining_flowers * flowers[i].b;
        max_sum = std::max(max_sum, sum);
    }
    std::cout << max_sum << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        SolveTest();
    }
    return 0;
}
