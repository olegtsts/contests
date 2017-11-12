#include <iostream>
#include <vector>

int main() {
    std::vector<size_t> strengths(6);
    size_t sum_of_strengths = 0;
    for (size_t i = 0; i < 6; ++i) {
        std::cin >> strengths[i];
        sum_of_strengths += strengths[i];
    }
    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = i + 1; j < 6; ++j) {
            for (size_t k = j + 1; k < 6; ++k) {
                if (2 * (strengths[i] + strengths[j] + strengths[k]) == sum_of_strengths) {
                    std::cout << "YES\n";
                    return 0;
                }
            }
        }
    }
    std::cout << "NO\n";
    return 0;
}
