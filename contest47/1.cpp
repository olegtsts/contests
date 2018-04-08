#include <limits>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string DoTest() {
    long long int d;
    std::cin >> d;
    std::string p;
    std::cin >> p;
    long long int total_points = 0;
    long long int power_points = 1;
    std::vector<long long int> prefix_points(p.size() + 1, 0);
    for (size_t i = 0; i < p.size(); ++i) {
        char s = p[i];
        if (s == 'C') {
            power_points *= 2;
        } else {
            total_points += power_points;
        }
        prefix_points[i + 1] = power_points;
    }
    long long int number_of_hacks = 0;
    while (total_points > d) {
        size_t last_cs_index = std::numeric_limits<size_t>::max();
        for (size_t i = 0; i + 1 < p.size(); ++i) {
            if (p[i] == 'C' && p[i + 1] == 'S') {
                last_cs_index = i;
            }
        }
        if (last_cs_index == std::numeric_limits<size_t>::max()) {
            if (total_points > d) {
                return "IMPOSSIBLE";
            }
        } else {
            p[last_cs_index] = 'S';
            p[last_cs_index + 1] = 'C';
            prefix_points[last_cs_index + 1] /= 2;
            total_points -= prefix_points[last_cs_index + 1];
            ++number_of_hacks;
        }
    }
    return std::to_string(number_of_hacks);
}
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ": " << DoTest() << std::endl;
    }
    return 0;
}
