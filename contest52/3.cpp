#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>

struct RectangleWithCount {
    long long int width;
    long long int height;
    long long int count;
};

long long GetGCD(long long int a, long long int b) {
    while (b > 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

long long int GetDivisorsCount(long long int x) {
    long long int divisor = 2;
    long long int total_divisors_count = 1;
    while (x > 1) {
        long long int current_multiplications = 0;
        while (x % divisor == 0) {
            x /= divisor;
            ++current_multiplications;
        }
        total_divisors_count *= (current_multiplications + 1);
        ++divisor;
    }
    return total_divisors_count;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<RectangleWithCount> rectangles(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> rectangles[i].width >> rectangles[i].height >> rectangles[i].count;
    }
    std::unordered_map<long long int, int> width_indexes;
    int max_width_index = 0;
    std::unordered_map<long long int, int> height_indexes;
    int max_height_index = 0;
    for (int i = 0; i < n; ++i) {
        auto width = rectangles[i].width;
        auto height = rectangles[i].height;
        if (width_indexes.count(width) == 0) {
            width_indexes[width] = max_width_index++;
        }
        if (height_indexes.count(height) == 0) {
            height_indexes[height] = max_height_index++;
        }
        if (width_indexes.size() * height_indexes.size() > static_cast<size_t>(n)) {
            std::cout << 0 << std::endl;
            return 0;
        }
    }
    std::vector<std::vector<long long int>> x(max_width_index, std::vector<long long int>(max_height_index, 0));
    for (int i = 0; i < n; ++i) {
        auto width_index = width_indexes[rectangles[i].width];
        auto height_index = height_indexes[rectangles[i].height];
        x[width_index][height_index] += rectangles[i].count;
    }
    for (int i = 0; i < max_width_index; ++i) {
        for (int j = 0; j < max_height_index; ++j) {
            if (x[i][j] == 0) {
                std::cout << 0 << std::endl;
                return 0;
            }
        }
    }
    std::vector<long long int> row_divisors(max_height_index, 0);
    long long int total_rows_gcd;
    bool is_gcd_initialized = false;
    for (int i = 0; i < max_height_index; ++i) {
        for (int j = 0; j < max_width_index; ++j) {
            row_divisors[i] += x[j][i];
            assert(row_divisors[i] >= 0);
        }
        if (is_gcd_initialized) {
            total_rows_gcd = GetGCD(total_rows_gcd, row_divisors[i]);
        } else {
            total_rows_gcd = row_divisors[i];
            is_gcd_initialized = true;
        }
    }

    for (int i = 0; i < max_height_index; ++i) {
        row_divisors[i] /= total_rows_gcd;
    }


    assert(total_rows_gcd >= 0);

    for (int i = 0; i < max_height_index; ++i) {
        for (int j = 0; j < max_width_index; ++j) {
            if (x[j][i] % row_divisors[i] != 0) {
                std::cout << 0 << std::endl;
                return 0;
            }
        }
    }
    std::vector<long long int> col_divisors(max_width_index);
    for (int i = 0; i < max_width_index; ++i) {
        col_divisors[i] = x[i][0] / row_divisors[0];
    }

    for (int i = 0; i < max_height_index; ++i) {
        for (int j = 0; j < max_width_index; ++j) {
            if (x[j][i] / row_divisors[i] > col_divisors[j] || x[j][i] != col_divisors[j] * row_divisors[i]) {
                std::cout << 0 << std::endl;
                return 0;
            }
        }
    }
    long long int total_col_gcd;
    bool is_totoal_col_gcd_initialized = false;
    for (int i = 0; i < max_width_index; ++i) {
        if (is_totoal_col_gcd_initialized) {
            total_col_gcd = GetGCD(total_col_gcd, col_divisors[i]);
        } else {
            total_col_gcd = col_divisors[i];
            is_totoal_col_gcd_initialized = true;
        }
    }
    std::cout << GetDivisorsCount(total_col_gcd) << std::endl;
    return 0;
}
