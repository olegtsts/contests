#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    int m;
    std::cin >> m;
    std::unordered_map<long double, int> counts;
    std::vector<long double> counts_vector;
    for (int i = 0; i < m; ++i) {
        long double a;
        long double b;
        long double c;
        char ch;
        std::cin >> ch >> a >> ch >> b >> ch >> ch >> c;
        long double result = (a + b) / c;
        if (counts.count(result) == 0) {
            counts[result] = 0;
        }
        ++counts[result];
        counts_vector.push_back(result);
    }
    for (int i = 0; i < m; ++i) {
        std::cout << counts[counts_vector[i]] << " ";
    }
    std::cout << std::endl;
    return 0;
}
