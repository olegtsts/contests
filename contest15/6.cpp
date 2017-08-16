#include <iostream>
#include <vector>
#include <tuple>

const uint64_t MAX_NUM = 1000000000000000001ul;

uint64_t get_iteration_simple(const int n, const uint64_t k,
                         std::vector<uint64_t>& a) {
    int iterations = 0;
    while (true) {
        ++iterations;
        for (int i = 1; i < n; ++i) {
            a[i] += a[i - 1];
            if (a[i] >= k) {
                return iterations;
            }
        }
    }
}

bool is_there_more_than_k_with_coeffs(
    const int n, const uint64_t k,
    std::vector<uint64_t>& a,
    std::vector<std::vector<uint64_t>>& coeffs
) {
    for (int i = 0; i < n; ++i) {
        uint64_t result = 0;
        for (int j = 0; j <= i; ++j) {
            if (static_cast<double>(a[j]) * static_cast<double>(coeffs[i][j]) > MAX_NUM) {
                return true;
            }
            result += coeffs[i][j] * a[j];
            if (result >= k) {
                return true;
            }
        }
    }
    return false;
}

std::tuple<std::vector<std::vector<uint64_t>>, bool> generate_mixed_coeffs(
    const int n,
    const uint64_t k,
    std::vector<std::vector<uint64_t>>& first_coeffs,
    std::vector<std::vector<uint64_t>>& second_coeffs
) {
    bool is_there_overflow = false;
    std::vector<std::vector<uint64_t>> new_coeffs(n);
    for (int i = 0; i < n; ++i) {
        new_coeffs[i].resize(i + 1, 0);
        for (int j = 0; j <= i; ++j) {
            new_coeffs[i][j] = 0;
            for (int k = j; k <= i; ++k) {
                if (static_cast<double>(second_coeffs[i][k]) * static_cast<double>(first_coeffs[k][j]) > MAX_NUM) {
                    is_there_overflow = true;
                }
                new_coeffs[i][j] += second_coeffs[i][k] * first_coeffs[k][j];
            }
        }
    }
    return std::make_tuple(new_coeffs, is_there_overflow);
}

uint64_t get_iteration_binsearch(const int n, const uint64_t k,
                            std::vector<uint64_t>& a) {
    uint64_t left = 0;
    uint64_t right = 1;
    std::vector<std::vector<std::vector<uint64_t>>> level_coeffs(100);
    level_coeffs[0].resize(n);
    std::vector<std::vector<uint64_t>> current_coeffs(n);
    for (int i = 0; i < n; ++i) {
        level_coeffs[0][i].resize(i + 1, 0);
        current_coeffs[i].resize(i + 1, 0);
        for (int j = 0; j <= i; ++j) {
            level_coeffs[0][i][j] = 1;
            current_coeffs[i][j] = (i == j ? 1 : 0);
        }
    }
    int diff_two_power = 0;
    while (true) {
        if (is_there_more_than_k_with_coeffs(n, k, a, level_coeffs[diff_two_power])) {
            break;
        } else {
            right *= 2;
            bool is_there_overflow;
            std::tie(level_coeffs[diff_two_power + 1], is_there_overflow) = generate_mixed_coeffs(
                n, k, level_coeffs[diff_two_power], level_coeffs[diff_two_power]);
            ++diff_two_power;
            if (is_there_overflow) {
                break;
            }
        }
    }
    while (right - left > 1) {
        uint64_t middle = left + (1ull << (diff_two_power - 1));
        std::vector<std::vector<uint64_t>> middle_coeffs;
        bool is_there_overflow;
        std::tie(middle_coeffs, is_there_overflow) = generate_mixed_coeffs(
            n, k, current_coeffs, level_coeffs[diff_two_power - 1]);
        if (is_there_overflow || is_there_more_than_k_with_coeffs(n, k, a, middle_coeffs)) {
            right = middle;
        } else {
            left = middle;
            current_coeffs = std::move(middle_coeffs);
        }
        --diff_two_power;
    }
    return left + 1;
}

bool is_there_more_than_k(const int n, const uint64_t k,
                    const std::vector<uint64_t>& a) {

    for (int i = 0; i < n; ++i) {
        if (a[i] >= k) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    uint64_t k;
    std::cin >> n >> k;
    bool still_zero = true;
    std::vector<uint64_t> a(n);
    int new_n = 0;
    for (int i = 0; i < n; ++i) {
        uint64_t number;
        std::cin >> number;
        if (number != 0 || !still_zero) {
            a[new_n++] = number;
        }
        if (number != 0) {
            still_zero = false;
        }
    }
    const int simple_algo_bound = 60;
    uint64_t result;
    if (is_there_more_than_k(new_n, k, a)) {
        result = 0;
    } else if (new_n >= simple_algo_bound) {
        result = get_iteration_simple(new_n, k, a);
    } else {
        result = get_iteration_binsearch(new_n, k, a);
    }
    std::cout << result << std::endl;
    return 0;
}
