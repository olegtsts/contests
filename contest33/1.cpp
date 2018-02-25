#include <iostream>
#include <vector>
#include <algorithm>

enum class RowType {
    HORIZONTAL_COVERED=0,
    VERTICAL_ABOVE_COVERED=1,
    NOT_COVERED=2,
    SECOND_HORIZONTAL_COVERED=3
};

void FillPossibleConfigurations(
    std::vector<std::vector<RowType>>& configurations,
    std::vector<RowType>& configuration_prefix,
    const int prefix_legnth,
    const int m
) {
    if (prefix_legnth == m) {
        configurations.push_back(configuration_prefix);
        return;
    }
    configuration_prefix[prefix_legnth] = RowType::NOT_COVERED;
    FillPossibleConfigurations(configurations, configuration_prefix, prefix_legnth + 1, m);
    if (prefix_legnth + 1 < m) {
        configuration_prefix[prefix_legnth] = RowType::HORIZONTAL_COVERED;
        configuration_prefix[prefix_legnth + 1] = RowType::SECOND_HORIZONTAL_COVERED;
        FillPossibleConfigurations(configurations, configuration_prefix, prefix_legnth + 2, m);
    }
    configuration_prefix[prefix_legnth] = RowType::VERTICAL_ABOVE_COVERED;
    FillPossibleConfigurations(configurations, configuration_prefix, prefix_legnth + 1, m);
}

void Transpose(int& n, int& m, std::vector<std::vector<bool>>& matrix) {
    std::vector<std::vector<bool>> another_matrix(n, std::vector<bool>(m, false));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            another_matrix[j][i] = matrix[i][j];
        }
    }
    matrix = std::move(another_matrix);
    std::swap(n,m);
}

void DoTest() {
    int n,m;
    std::cin >> n >> m;
    int x;
    std::cin >> x;
    int modulo;
    std::cin >> modulo;
    std::vector<std::vector<bool>> matrix(m, std::vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            char symbol;
            std::cin >> symbol;
            if (symbol == 'A') {
                matrix[i][j] = true;
            }
        }
    }
    if (n > m) {
        Transpose(n,m,matrix);
    }
    std::vector<std::vector<RowType>> configurations;
    std::vector<RowType> configuration_prefix(n, RowType::NOT_COVERED);
    FillPossibleConfigurations(configurations, configuration_prefix, 0, n);
    std::cerr << "Generated " << configurations.size() << " presets" << std::endl;
    std::vector<std::vector<int>> mask_voices_options_count((1 << (n + 1)), std::vector<int>(x + 1, 0));

    mask_voices_options_count[0][0] = 1;
    for (int i = 0; i < m; ++i) {
        std::vector<std::vector<int>> swap_mask_voices_options_count((1 << (n + 1)), std::vector<int>(x + 1, 0));
        for (auto& configuration: configurations) {
            size_t new_mask = 0;
            size_t old_mask = 0;
            int additional_voices = 0;
            for (size_t j = 0; j < configuration.size(); ++j) {
                if (configuration[j] == RowType::NOT_COVERED) {
                    new_mask |= (1ull << j);
                } else if (configuration[j] == RowType::VERTICAL_ABOVE_COVERED) {
                    old_mask |= (1ull << j);
                    additional_voices += (i > 0 && matrix[i - 1][j] && matrix[i][j]) ? 1 : 0;
                } else if (configuration[j] == RowType::HORIZONTAL_COVERED) {
                    additional_voices += (matrix[i][j] && matrix[i][j + 1]) ? 1 : 0;
                }
            }
            for (int k = 0; k + additional_voices <= x; ++k) {
                swap_mask_voices_options_count[new_mask][k + additional_voices] += mask_voices_options_count[old_mask][k];
                swap_mask_voices_options_count[new_mask][k + additional_voices] %= modulo;
            }
        }
        std::swap(mask_voices_options_count, swap_mask_voices_options_count);
        std::cerr << "Done " << i << " row" << std::endl;
    }
    std::cout << mask_voices_options_count[0][x] << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        DoTest();
    }
    return 0;
}
