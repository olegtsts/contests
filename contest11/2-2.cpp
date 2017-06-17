#include <iostream>
#include <vector>

void replace_with_prefix_sums(
    std::vector<int>& counters
) {
    for (size_t i = 1; i < counters.size(); ++i) {
        counters[i] += counters[i - 1];
    }
}

int main() {
    std::vector<int> counters(200002, 0);
    int n,k,q;
    std::cin >> n >> k >> q;
    for (int i = 0; i < n; ++i) {
        int l,r;
        std::cin >> l >> r;
        ++counters[l];
        --counters[r + 1];
    }
    replace_with_prefix_sums(counters);
    for (size_t i = 0; i < counters.size(); ++i) {
        counters[i] = counters[i] >= k ? 1 : 0;
    }
    replace_with_prefix_sums(counters);
    for (int i = 0; i < q; ++i) {
        int a, b;
        std::cin >> a >> b;
        std::cout << counters[b] - counters[a - 1] << std::endl;
    }
    return 0;
}
