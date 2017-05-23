#include <iostream>
#include <vector>

inline long long int get_counts(std::vector<long long int>& counts, int all_even, int last_even, int last_used) {
    return counts[all_even + last_even * 2 + last_used * 4];
}

inline void set_counts(std::vector<long long int>& counts, int all_even, int last_even, int last_used, long long int number) {
    counts[all_even + last_even * 2 + last_used * 4] = number;
}

int main () {
    long long int n;
    std::cin >> n;
    std::vector<long long int> counts(8, 0);
    for (size_t i = 0; i < n; ++i) {
        long long int new_number;
        std::cin >> new_number;
        std::vector<long long int> new_counts(8, n + 1);
        int new_even = (new_number % 2 == 0 ? 0 : 1);
        // all_even = 0, last_even = 0, last_used = 0
        for (int target_last_used = 0; target_last_used < 2; ++target_last_used) {
            for (int target_last_even = 0; target_last_even < 2; ++target_last_even) {
                for (int target_all_even = 0; target_all_even < 2; ++target_all_even) {
                    int target_last_wrong_even = (new_even != target_last_even) ? 1 : 0;
                    int last_used = (target_last_wrong_even + target_last_used) % 2;
                    int last_even = (target_all_even + target_last_used) % 2;
                    int all_even = target_all_even;
                    if (!(last_used == 1 && i == 0)) {
                        set_counts(new_counts, target_all_even, target_last_even, target_last_used, get_counts(counts, all_even, last_even, last_used) + (target_last_used != 0 ? 1 : 0));
//                        std::cout << "set state (" << target_all_even << "," << target_last_even << "," << target_last_used << ") to " << get_counts(counts, all_even, last_even, last_used) + (target_last_used != 0 ? 1 : 0) << " with addon " << (target_last_used != 0 ? 1 : 0)  << std::endl;
                    }
                }
            }
        }
        counts = new_counts;
    }
    for (int target_even = 1; target_even >= 0; --target_even) {
        long long int min_steps = n + 1;
        for (int last_used = 0; last_used < 2; ++last_used) {
            if (min_steps > get_counts(counts, target_even, target_even, last_used)) {
                min_steps = get_counts(counts, target_even, target_even, last_used);
            }
        }
        if (min_steps == n + 1) {
            std::cout << -1 << std::endl;
        } else {
            std::cout << min_steps << std::endl;
        }
    }
    return 0;
}
