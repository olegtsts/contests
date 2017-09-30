#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> counts(n, 0);
    std::vector<int> permutation(n, 0);
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        --a;
        ++counts[a];
        permutation[i] = a;
    }
    std::vector<bool> was_remained(n, false);
    int first_not_used_number = 0;
    int changed_elements = 0;
    for (int i = 0; i < n; ++i) {
        while (first_not_used_number < n && counts[first_not_used_number] > 0) {
            ++first_not_used_number;
        }
        if (was_remained[permutation[i]]) {
            permutation[i] = first_not_used_number;
            ++changed_elements;
            ++first_not_used_number;
        } else {
            if (counts[permutation[i]] > 1 && first_not_used_number < permutation[i]) {
                --counts[permutation[i]];
                permutation[i] = first_not_used_number;
                ++changed_elements;
                ++first_not_used_number;
            } else if (counts[permutation[i]] > 1 && first_not_used_number > permutation[i]) {
                --counts[permutation[i]];
                was_remained[permutation[i]] = true;
            } else if (counts[permutation[i]] == 1) {
                was_remained[permutation[i]] = true;
            }
        }
    }
    std::cout << changed_elements << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << permutation[i] + 1;
        if (i + 1 < n) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
