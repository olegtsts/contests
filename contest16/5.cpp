#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

const long long int MODULO = 1000000007;

int main() {
    int n;
    std::cin >> n;
    std::vector<long long int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<bool> is_used(n, false);
    std::vector<int> same_class_sizes;
    for (int i = 0; i < n; ++i) {
        if (!is_used[i]) {
            int class_size = 1;
            for (int j = i + 1; j < n; ++j) {
                if (a[i] * a[j] == static_cast<long long int>(sqrt(a[i] * a[j])) * static_cast<long long int>(sqrt(a[i] * a[j]))) {
                    ++class_size;
                    is_used[j] = true;
                }
            }
            same_class_sizes.push_back(class_size);
        }
    }

    std::vector<std::vector<int>> binom(n + 2);
    for (int i = 0; i < n + 2; ++i) {
        binom[i].resize(n + 2, 0);
        binom[i][0] = (i == 0 ? 1 : 0);
    }
    for (int i = 1; i < n + 2; ++i) {
        for (int j = 0; j < n + 2; ++j) {
            if (j >= 1) {
                binom[j][i] = binom[j][i - 1] + binom[j - 1][i - 1];
            } else {
                binom[j][i] = binom[j][i - 1];
            }
            binom[j][i] %= MODULO;
        }
    }
    std::vector<int> prev_perm_counts(1, 1);
    std::vector<int> perm_counts;
    int total_numbers_count = 0;
    int prev_total_numbers_count = 0;
    for (size_t i = 0; i < same_class_sizes.size(); ++i) {
        total_numbers_count += same_class_sizes[i];
        perm_counts.resize(total_numbers_count + 1, 0);
        for (int errors_count = 0; errors_count < total_numbers_count; ++errors_count) {
            for (int dropped_errors = 0; dropped_errors < same_class_sizes[i] + 1; ++dropped_errors) {
                for (int rest_places = 0; rest_places < std::min(prev_total_numbers_count + 2, same_class_sizes[i] - dropped_errors + 1); ++rest_places) {
                    int new_errors = same_class_sizes[i] - dropped_errors - rest_places;
                    int old_errors_count = errors_count + dropped_errors - new_errors;
                    if (old_errors_count >= 0
                        && old_errors_count < prev_total_numbers_count + 1
                        && new_errors >= 0
                        && new_errors < total_numbers_count + 1
                        && dropped_errors + rest_places >= 1
                    ) {
                        long long int addon = prev_perm_counts[old_errors_count];
                        addon *= binom[dropped_errors][old_errors_count];
                        addon %= MODULO;
                        addon *= binom[rest_places][prev_total_numbers_count + 1 - old_errors_count];
                        addon %= MODULO;
                        addon *= binom[dropped_errors + rest_places - 1][same_class_sizes[i] - 1];
                        addon %= MODULO;
                        perm_counts[errors_count] += addon;
                        perm_counts[errors_count] %= MODULO;
                    }
                }
            }
        }
        prev_total_numbers_count = total_numbers_count;
        prev_perm_counts = std::move(perm_counts);
    }
    std::vector<long long int> factorial(n + 1);
    factorial[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        factorial[i] = i * factorial[i - 1];
        factorial[i] %= MODULO;
    }
    long long int result;
    if (prev_perm_counts.size() == 0) {
        result = 1;
    } else {
        result = prev_perm_counts[0];
    }
    for (auto& size: same_class_sizes) {
        result *= factorial[size];
        result %= MODULO;
    }
    std::cout << result << std::endl;
    return 0;
}
