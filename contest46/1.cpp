#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<int> columns_counts(n, 0);
    for (int i = 0; i < m; ++i) {
        int number;
        std::cin >> number;
        --number;
        ++columns_counts[number];
    }
    std::cout << *std::min_element(columns_counts.begin(), columns_counts.end()) << std::endl;
    return 0;
}

