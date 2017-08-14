#include <iostream>
#include <vector>
#include <algorithm>

struct Multipliers {
    int two_count = 0;
    int five_count = 0;

    int GetDiff() const noexcept {
        return two_count - five_count;
    }
};

int pack(const int n1, const int k1, const int diff1, const int n, const int k, const int min_difference) {
    return ((diff1 - min_difference) * (n + 1) + n1) * (k + 1) + k1;
}

int main() {
    int n,k;
    std::cin >> n >> k;
    std::vector<Multipliers> a(n, Multipliers{0, 0});
    for (int i = 0; i < n; ++i) {
        uint64_t number;
        std::cin >> number;
        while (number % 2 == 0) {
            number /= 2;
            ++a[i].two_count;
        }
        while (number % 5 == 0) {
            number /= 5;
            ++a[i].five_count;
        }
    }
    const int max_difference = 60;
    const int min_difference = -26;
    std::vector<int> responses((max_difference - min_difference + 1) * (n + 1) * (k + 1), -1);
    Multipliers mult{0, 0};
    for (int i = 0; i < n + 1; ++i) {
        if (i < k + 1) {
            responses[pack(i, i, mult.GetDiff(), n, k, min_difference)] = std::min(mult.two_count, mult.five_count);
//            std::cout << " init set " << i << " " << i << " " << mult.GetDiff() << " = " << std::min(mult.two_count, mult.five_count) << std::endl;
        }
        responses[pack(i, 0, 0, n, k, min_difference)] = 0;
//        std::cout << " init set " << i << " " << 0 << " " << 0 << " = " << 0 << std::endl;
        mult.two_count += a[i].two_count;
        mult.five_count += a[i].five_count;
    }
    for (int n1 = 0; n1 < n + 1; ++n1) {
        for (int k1 = 0; k1 < n1; ++k1) {
            for (int diff1 = min_difference; diff1 < max_difference; ++diff1) {
                int max_zeros = responses[pack(n1 - 1, k1, diff1, n, k, min_difference)];
                if (k1 > 0) {
                    int new_diff = diff1 - a[n1 - 1].two_count + a[n1 - 1].five_count;
                    if (new_diff >= min_difference && new_diff < max_difference) {
                        int old_max_zeros = responses[pack(n1 - 1, k1 - 1, new_diff, n, k, min_difference)];
                        if (old_max_zeros >= 0) {
                            int old_two_count;
                            int old_five_count;
                            if (new_diff >= 0) {
                                old_two_count = old_max_zeros + new_diff;
                                old_five_count = old_max_zeros;
                            } else {
                                old_two_count = old_max_zeros;
                                old_five_count = old_max_zeros - new_diff;
                            }
                            int new_two_count = old_two_count + a[n1 - 1].two_count;
                            int new_five_count = old_five_count + a[n1 - 1].five_count;
                            int new_max_zeros = std::min(new_two_count, new_five_count);
                            if (max_zeros < new_max_zeros) {
                                max_zeros = new_max_zeros;
                            }
                        }
                    }
                }
                responses[pack(n1, k1, diff1, n, k, min_difference)] = max_zeros;
                if (max_zeros > 0) {
//                    std::cout << " set " << n1 << " " << k1 << " "  << diff1 << " = " << max_zeros << std::endl;
                }
            }
        }
    }
    int final_max_zeros = 0;
    for (int diff1 = min_difference; diff1 < max_difference; ++diff1) {
        int current_zeros = responses[pack(n, k, diff1, n, k, min_difference)];
        if (final_max_zeros < current_zeros) {
            final_max_zeros = current_zeros;
        }
    }
    std::cout << final_max_zeros << std::endl;
    return 0;
}
