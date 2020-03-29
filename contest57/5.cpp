#include <iostream>
#include <unordered_map>
#include <vector>
#include <numeric>

int MODULO = 1000000007;

void GetTotalScore(
    int node,
    const std::vector<std::vector<int>>& edges,
    const std::vector<long long int>& weights,
    std::vector<bool>* is_visited,
    const std::unordered_map<long long int, int>& root_counts,
    int* total_score
) {
    (*is_visited)[node] = true;
    for (auto [gcd_value, counter] : root_counts) {
        *total_score += static_cast<int>((static_cast<long long int>(counter) * gcd_value) % static_cast<long long int>(MODULO));
        *total_score %= MODULO;
    }
    for (auto child : edges[node]) {
        if (!(*is_visited)[child]) {
            std::unordered_map<long long int, int> new_root_counts;
            new_root_counts[weights[child]] = 1;
            for (auto [gcd_value, counter] : root_counts) {
                long long int new_gcd_value = std::gcd(gcd_value, weights[child]);
                new_root_counts[new_gcd_value] += counter;
                new_root_counts[new_gcd_value] %= MODULO;
            }
            GetTotalScore(child, edges, weights, is_visited, new_root_counts, total_score);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<long long int> weights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
    std::vector<std::vector<int>> edges(n);
    for (int i = 0; i < n - 1; ++i) {
        int a,b;
        std::cin >> a >> b;
        --a;
        --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    std::vector<bool> is_visited(n, false);
    int total_score = 0;
    std::unordered_map<long long int, int> root_counters;
    root_counters[weights[0]] = 1;
    GetTotalScore(0, edges, weights, &is_visited, root_counters, &total_score);
    std::cout << total_score << std::endl;
    return 0;
}
