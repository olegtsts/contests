#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

int GetGreedyResult(std::vector<std::pair<int, int>>* all_pairs, int first_coef, int second_coef, int r, int b) {
    std::sort(
        all_pairs->begin(),
        all_pairs->end(),
        [first_coef, second_coef](const std::pair<int, int>& first_pair, const std::pair<int, int>& second_pair) {
            return first_pair.first * first_coef + first_pair.second * second_coef < second_pair.first * first_coef + second_pair.second * second_coef;
        });
    int result_count = 0;
    for (auto current_pair : *all_pairs) {
        if (current_pair.first <= r && current_pair.second <= b) {
            r -= current_pair.first;
            b -= current_pair.second;
            ++result_count;
        }
        if (r == 0 && b == 0) {
            break;
        }
    }
    return result_count;
}

int ProcessTest() {
    int r,b;
    std::cin >> r >> b;
    std::vector<std::pair<int, int>> all_pairs;
    for (int i = 0; i <= 32; ++i) {
        for (int j = 0; j <= 32; ++j) {
            if (i > 0 || j > 0) {
                all_pairs.push_back(std::make_pair(i, j));
            }
        }
    }
    int result_count = 0;
    for (int i = 0; i <= 32; ++i) {
        for (int j = 0; j <= 32; ++j) {
            if (i > 0 || j > 0) {
                result_count = std::max(result_count, GetGreedyResult(&all_pairs, i, j, r, b));
            }
        }
    }
    return result_count;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ": " << ProcessTest() << std::endl;
    }
    return 0;
}
