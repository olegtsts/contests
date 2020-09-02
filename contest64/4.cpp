#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <tuple>

struct Train {
    int64_t m;
    int64_t index;

    bool operator<(const Train& other) const {
        return std::forward_as_tuple(m, index) < std::forward_as_tuple(other.m, other.index);
    }
};

void ProcessOption(
    const std::vector<Train>& mins, int64_t m, int64_t mi, int64_t k,
    size_t& min_cancelled_trains, int64_t& result_mi,
    size_t& result_left_index,
    size_t& result_right_index
) {
    int64_t right_index = std::lower_bound(mins.begin(), mins.end(), Train{mi, -1}) - mins.begin();
    int64_t left_index = std::upper_bound(mins.begin(), mins.end(), Train{(mi - k + m / 2) % (m / 2), static_cast<int64_t>(mins.size())}) - mins.begin();
    if ((right_index - left_index + mins.size()) % mins.size() < min_cancelled_trains) {
        min_cancelled_trains = (right_index - left_index + mins.size()) % mins.size();
        result_mi = mi;
        result_left_index = left_index;
        result_right_index = right_index;
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    int64_t n,h,m,k;
    std::cin >> n >> h >> m >> k;
    std::vector<Train> mins;
    for (int64_t i = 0; i < n; ++i) {
        int64_t mi;
        std::cin >> mi >> mi;
        mins.push_back({mi % (m / 2), i + 1});
    }
    std::sort(mins.begin(), mins.end());
    size_t min_cancelled_trains = std::numeric_limits<size_t>::max();
    int64_t result_mi;
    size_t left_index, right_index;
    for (Train train : mins) {
        ProcessOption(mins, m, train.m, k, min_cancelled_trains, result_mi, left_index, right_index);
        ProcessOption(mins, m, (train.m + k) % (m / 2), k, min_cancelled_trains, result_mi, left_index, right_index);
    }
    if (right_index < left_index) {
        right_index += mins.size();
    }
    std::cout << min_cancelled_trains << " " << result_mi << std::endl;
    for (size_t i = left_index; i < right_index; ++i) {
        std::cout << mins[i % mins.size()].index << " ";
    }
    std::cout << std::endl;
    return 0;
}
