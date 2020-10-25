#include <iostream>
#include <optional>
#include <vector>

int Encode(int mod, int num_count, int k) {
    int state = num_count;
    state *= k;
    state += mod;
    return state;
}

void UpdateOptionalMax(const std::optional<int>& input, const std::optional<int>& addon, std::optional<int>& target) {
    if (!input.has_value()) {
        return;
    }
    if (!addon.has_value()) {
        return;
    }
    int new_value = input.value() + addon.value();
    if (!target.has_value()) {
        target = new_value;
        return;
    }
    if (target.value() < new_value) {
        target = new_value;
        return;
    }
}

int main() {
    int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    // mod and count of numbers => max sum
    std::vector<std::optional<int>> prev_submatrix_state(k, std::nullopt);
    prev_submatrix_state[0] = 0;
    for (int i = 0; i < n; ++i) {
        std::vector<std::optional<int>> prev_prefix_state(k * (m / 2 + 1), std::nullopt);
        prev_prefix_state[Encode(0, 0, k)] = 0;
        for (int j = 0; j < m; ++j) {
            std::vector<std::optional<int>> new_prefix_state(k * (m / 2 + 1), std::nullopt);
            for (int num_count = 0; num_count <= m / 2; ++num_count) {
                for (int mod = 0; mod < k; ++mod) {
                    // not choosing j
                    UpdateOptionalMax(prev_prefix_state[Encode(mod, num_count, k)], 0, new_prefix_state[Encode(mod, num_count, k)]);
                    // choosing j
                    if (num_count > 0) {
                        UpdateOptionalMax(prev_prefix_state[Encode(((mod - matrix[i][j]) % k + k) % k, num_count - 1, k)], matrix[i][j], new_prefix_state[Encode(mod, num_count, k)]);
                    }
                }
            }
            prev_prefix_state = std::move(new_prefix_state);
        }
        std::vector<std::optional<int>> new_submatrix_state(k, std::nullopt);
        for (int mod = 0; mod < k; ++mod) {
            for (int last_mod = 0; last_mod < k; ++last_mod) {
                for (int last_num_count = 0; last_num_count <= m / 2; ++last_num_count) {
                    UpdateOptionalMax(prev_submatrix_state[((mod - last_mod) % k + k) % k], prev_prefix_state[Encode(last_mod, last_num_count, k)], new_submatrix_state[mod]);
                }
            }
        }
        prev_submatrix_state = std::move(new_submatrix_state);
    }
    std::cout << prev_submatrix_state[0].value() << std::endl;
    return 0;
}

