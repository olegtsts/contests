#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <limits>
#include <algorithm>

bool IsPossible(
    std::vector<long long int> gramms,
    std::vector<std::vector<long long int>> formulas,
    const long long int m,
    const long long int target_lead
) {
    gramms[0] -= target_lead;
    while (true) {
        long long int negative_index = -1;
        for (long long int i = 0; i < m; ++i) {
            if (gramms[i] < 0) {
                negative_index = i;
                break;
            }
        }
        if (negative_index == -1) {
            return true;
        }
        if (formulas[negative_index][negative_index] > 0) {
            return false;
        }
        for (long long int i = 0; i < m; ++i) {
            if (i != negative_index && formulas[i][negative_index] > 0) {
                for (long long int j = 0; j < m; ++j) {
                    if (formulas[i][negative_index] != 0 && std::numeric_limits<long long int>::max() / formulas[i][negative_index] < formulas[negative_index][j]) {
                        return false;
                    }
                    long long int addon = formulas[negative_index][j] * formulas[i][negative_index];
                    if (std::numeric_limits<long long int>::max() - addon < formulas[i][j]) {
                        return false;
                    }
                    formulas[i][j] += addon;
                }
                formulas[i][negative_index] = 0;
            }
        }
        for (long long int i = 0; i < m; ++i) {
            if (gramms[negative_index] != 0 && std::numeric_limits<long long int>::max() / (-gramms[negative_index]) < formulas[negative_index][i]) {
                return false;
            }
            long long int addon = formulas[negative_index][i] * gramms[negative_index];
            if (std::numeric_limits<long long int>::min() - addon > gramms[i]) {
                return false;
            }
            gramms[i] += addon;
        }
        gramms[negative_index] = 0;
    }
    assert(false);
}

long long int DoTest() {
    long long int m;
    std::cin >> m;
    std::vector<std::pair<long long int, long long int>> ingredients(m);
    std::vector<std::vector<long long int>> formulas(m, std::vector<long long int>(m, 0));
    for (long long int i = 0; i < m; ++i) {
        long long int first_ingredient, second_ingredient;
        std::cin >> first_ingredient >> second_ingredient;
        --first_ingredient;
        --second_ingredient;
        ++formulas[i][first_ingredient];
        ++formulas[i][second_ingredient];
    }
    std::vector<long long int> gramms(m);
    for (long long int i = 0; i < m; ++i) {
        std::cin >> gramms[i];
    }
    long long int lower_lead = 0;
    long long int upper_lead = 0;
    for (long long int i = 0; i < m; ++i) {
        upper_lead += gramms[i];
    }
    ++upper_lead;
    while (upper_lead - lower_lead > 1) {
        long long int middle_lead = (upper_lead + lower_lead) / 2;
        if (IsPossible(gramms, formulas, m, middle_lead)) {
            lower_lead = middle_lead;
        } else {
            upper_lead = middle_lead;
        }
    }
    return lower_lead;
}

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ": " << DoTest() << std::endl;
    }
    return 0;
}
