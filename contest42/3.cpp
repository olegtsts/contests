#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    long long int n;
    std::cin >> n;
    std::vector<long long int> levels(n);
    std::vector<long long int> sum_of_first_numbers(n + 1, 0);
    std::set<long long int> remained_levels;
    for (long long int i = 0; i < n; ++i) {
        std::cin >> levels[i];
        sum_of_first_numbers[i + 1] = i + 1 + sum_of_first_numbers[i];
        remained_levels.insert(i);
    }
    long long int current_levels_count = 0;
    long long int target_sum = 0;
    for (long long int i = 0; i < n; ++i) {
        long long int levels_above = levels[i];
        target_sum += current_levels_count - 1 - levels_above;
        while (current_levels_count - 1 < levels_above) {
            auto helping_level_it = remained_levels.upper_bound(i);
            --helping_level_it;
            auto helping_level = *helping_level_it;
            target_sum += i - helping_level + 1;
            current_levels_count += 1;
//            std::cout << "used " << helping_level << std::endl;
            remained_levels.erase(helping_level);
        }
//        std::cout << "after " << levels_above << " target_sum = " << target_sum << " current_levels_count = " << current_levels_count << std::endl;
    }
    std::cout << target_sum << std::endl;
    return 0;
}
