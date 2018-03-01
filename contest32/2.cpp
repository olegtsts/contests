#include <iostream>
#include <vector>
#include <algorithm>

void compute_messages(std::vector<int>& counts, int cur, int to, int k) {
    if (to != 0) {
        counts[cur] += counts[to - 1];
        int from = std::min(std::max(to + k, cur - k), int(counts.size()));
        int end_to = std::min(int(counts.size()), cur + k + 1);
        counts[cur] += end_to - from;

    } else {
        counts[cur] += std::min(k, cur) + 1;
        counts[cur] += std::min(int(counts.size() - cur - 1), k);
    }
}

int main () {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> counts(n, 0);
    for (size_t i = 0; i < n; ++i) {
        int to;
        std::cin >> to;
        compute_messages(counts, i, to, k);
        std::cout << counts[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
