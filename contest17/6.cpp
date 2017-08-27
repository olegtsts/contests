#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

std::tuple<int, int, std::vector<std::vector<bool>>> GetInverseBoard(
    const int n,
    const int m,
    const std::vector<std::vector<bool>>& is_wall
) {
    std::vector<std::vector<bool>> new_is_wall(m);
    for (int i = 0; i < m; ++i) {
        new_is_wall[i].resize(n);
        for (int j = 0; j < n; ++j) {
            new_is_wall[i][j] = is_wall[j][i];
        }
    }
    return std::make_tuple(m, n, new_is_wall);
}

std::tuple<uint16_t, bool, bool> Unpack(size_t index) {
    bool is_prev = (index % 2 == 1);
    index /= 2;
    bool is_missed = (index % 2 == 1);
    index /= 2;
    uint16_t mask = index;
    return std::make_tuple(mask, is_missed, is_prev);
}

size_t pack(const uint16_t mask, const bool is_missed, const bool is_prev) {
    size_t index = 0;
    index += mask;
    index *= 2;
    index += (is_missed ? 1 : 0);
    index *= 2;
    index += (is_prev ? 1 : 0);
    return index;
}
const long long int MODULO = 1000000007;

void TransferState(
    const size_t index,
    std::vector<long long int>& dp,
    std::vector<long long int>& new_dp,
    const uint16_t new_mask,
    const bool new_is_missed,
    const bool new_is_prev
) {
    if (dp[index]) {
        new_dp[pack(new_mask, new_is_missed, new_is_prev)] += dp[index];
        new_dp[pack(new_mask, new_is_missed, new_is_prev)] %= MODULO;
        uint16_t mask;
        bool is_missed;
        bool is_prev;
        std::tie(mask, is_missed, is_prev) = Unpack(index);
    }
}

void MoveState(
    std::vector<long long int>& dp,
    std::vector<long long int>& new_dp
) {
    std::swap(dp, new_dp);
    for (int i = 0; i < 262144; ++i) {
        new_dp[i] = 0;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<bool>> is_wall(n);
    for (int i = 0; i < n; ++i) {
        is_wall[i].resize(m);
        for  (int j = 0; j < m; ++j) {
            char ch;
            std::cin >> ch;
            is_wall[i][j] = (ch == 'x');
        }
    }
    if (m > n) {
        std::tie(n, m, is_wall) = GetInverseBoard(n, m, is_wall);
    }

    std::vector<long long int> dp(262144, 0);
    std::vector<long long int> new_dp(262144, 0);
    dp[pack(0, false, false)] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            uint16_t current_bit = (uint16_t(1) << j);
            for (size_t index = 0; index < 262144; ++index) {
                if (dp[index] > 0) {
                    uint16_t mask;
                    bool is_missed;
                    bool is_prev;
                    std::tie(mask, is_missed, is_prev) = Unpack(index);
                    if (is_wall[i][j]) {
                        TransferState(index, dp, new_dp, mask & ~current_bit, is_missed, false);
                    } else {
                        // Will place logic
                        TransferState(index, dp, new_dp, mask | current_bit, is_missed, true);

                        // Will not place logic
                        bool new_is_missed = !is_prev && !(mask & current_bit);
                        if ((!is_missed && new_is_missed) || !new_is_missed) {
                            TransferState(index, dp, new_dp, mask, (new_is_missed ? true : is_missed), is_prev);
                        }
                    }
                }
            }
            MoveState(dp, new_dp);
        }
        for (size_t index = 0; index < 262144; ++index) {
            if (dp[index] > 0) {
                uint16_t mask;
                bool is_missed;
                bool is_prev;
                std::tie(mask, is_missed, is_prev) = Unpack(index);
                TransferState(index, dp, new_dp, mask, is_missed, false);
            }
        }
        MoveState(dp, new_dp);
    }
    long long int result = 0;
    for (auto& options: dp) {
        result += options;
        result %= MODULO;
    }
    std::cout << result << std::endl;
    return 0;
}
