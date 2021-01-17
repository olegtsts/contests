#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


template <typename BiOp>
class StaticRangeQuery {
public:
    StaticRangeQuery(const std::vector<int>& input_vector) : values(GetLowerLog(input_vector.size()) + 1, std::vector<int>(input_vector.size())) {
        for (size_t i = 0; i < input_vector.size(); ++i) {
            values[0][i] = input_vector[i];
        }
        for (size_t level = 1; level < values.size(); ++level) {
            for (size_t i = 0; i < input_vector.size(); ++i) {
                values[level][i] = values[level - 1][i];
                size_t next_segment_start = i + (1 << (level - 1));
                if (next_segment_start < input_vector.size()) {
                    values[level][i] = BiOp::Apply(values[level - 1][i], values[level - 1][next_segment_start]);
                }
            }
        }
    }
    int GetValue(size_t left, size_t right) {
        assert(right > left);
        size_t level = GetLowerLog(right - left);
        return BiOp::Apply(values[level][left], values[level][right - (1 << level)]);
    }
private:
    static size_t GetLowerLog(size_t size) {
        size_t lower_number = 1;
        size_t lower_log = 0;
        while (size >= lower_number) {
            ++lower_log;
            lower_number <<= 1;
        }
        return lower_log - 1;
    }

    std::vector<std::vector<int>> values;
};

class MaxOp {
public:
    static int Apply(const int first, const int second) {
        return std::max(first, second);
    }
};

class MinOp {
public:
    static int Apply(const int first, const int second) {
        return std::min(first, second);
    }
};


void SolveTest() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> prefix_sums(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        char symbol;
        std::cin >> symbol;
        if (symbol == '+') {
            prefix_sums[i + 1] = prefix_sums[i] + 1;
        } else {
            prefix_sums[i + 1] = prefix_sums[i] - 1;
        }
    }
    StaticRangeQuery<MaxOp> range_max_query(prefix_sums);
    StaticRangeQuery<MinOp> range_min_query(prefix_sums);
    for (int i = 0; i < m; ++i) {
        int l, r;
        std::cin >> l >> r;
        --l;
        int max_value = range_max_query.GetValue(0, l + 1);
        int min_value = range_min_query.GetValue(0, l + 1);
        if (r < n) {
            max_value = std::max(max_value, range_max_query.GetValue(r + 1, n + 1) - prefix_sums[r] + prefix_sums[l]);
            min_value = std::min(min_value, range_min_query.GetValue(r + 1, n + 1) - prefix_sums[r] + prefix_sums[l]);
        }
        std::cout << max_value - min_value + 1 << std::endl;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        SolveTest();
    }
    return 0;
}
