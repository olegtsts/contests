#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include <limits>
#include <unordered_set>

int GetCycleLength(int first_node, int second_node, const std::vector<int>& prev_node) {
    std::unordered_map<int, int> first_parent_distance;
    int current_node = first_node;
    int current_distance = 0;
    while (current_node >= 0) {
        first_parent_distance[current_node] = current_distance++;
        current_node = prev_node[current_node];
    }
    current_node = second_node;
    current_distance = 0;
    while (current_node >= 0) {
        if (first_parent_distance.count(current_node) > 0) {
            return current_distance + first_parent_distance[current_node] + 1;
        }
        ++current_distance;
        current_node = prev_node[current_node];
    }
    assert(false);
}

std::optional<int> FindMinimalCycle(int start_node, const std::vector<std::unordered_set<int>>& graph, int max_bfs_depth) {
    std::vector<int> current_layer;
    current_layer.push_back(start_node);
    std::vector<bool> is_visited(graph.size(), false);
    std::vector<int> layer_num(graph.size(), -1);
    std::vector<int> prev_node(graph.size(), -1);
    for (int i = 0; i <= max_bfs_depth; ++i) {
        std::vector<int> next_layer;
        for (auto node : current_layer) {
            is_visited[node] = true;
            layer_num[node] = i;
            for (auto neighbour : graph[node]) {
                if (is_visited[neighbour]) {
                    if (prev_node[node] != neighbour) {
                        int cycle_length = GetCycleLength(node, neighbour, prev_node);
                        if (cycle_length >= 3) {
                            return cycle_length;
                        }
                    }
                } else {
                    prev_node[neighbour] = node;
                    next_layer.push_back(neighbour);
                }
            }
        }
        if (next_layer.size() == 0) {
            return {};
        }
        current_layer = std::move(next_layer);
    }
    return {};
}

int main() {
    std::ios::sync_with_stdio(false);
    int max_n = 1000001;
    std::vector<char> prime (max_n+1, true);
    prime[0] = prime[1] = false;
    for (int i=2; i<=max_n; ++i)
        if (prime[i])
            if (i * 1ll * i <= max_n)
                for (int j=i*i; j<=max_n; j+=i)
                    prime[j] = false;

    std::vector<int> primes;
    for (int i = 2; i <= max_n; ++i) {
        if (prime[i]) {
            primes.push_back(i);
        }
    }
    const int max_bfs_depth = 170;
    std::unordered_map<int, int> prime_index;
    for (size_t i = 0; i < primes.size(); ++i) {
        prime_index[primes[i]] = static_cast<int>(i + 1);
    }
    int n;
    std::cin >> n;
    std::vector<std::unordered_set<int>> graph(primes.size() + 1);
    bool is_there_duplicate_edges = false;
    for (int i = 0; i < n; ++i) {
        int number;
        std::cin >> number;
        std::vector<int> primes_inside;
        for (size_t i = 0; i < primes.size() && primes[i] <= 1000; ++i) {
            int degree = 0;
            while (number % primes[i] == 0) {
                number /= primes[i];
                degree = 1 - degree;
            }
            if (degree == 1) {
                primes_inside.push_back(primes[i]);
            }
        }
        if (prime[number]) {
            primes_inside.push_back(number);
            number = 1;
        }
        assert(number == 1);
        assert(primes_inside.size() <= 2);
        if (primes_inside.size() == 0) {
            std::cout << 1 << std::endl;
            return 0;
        } else if (primes_inside.size() == 1) {
            int node = prime_index[primes_inside[0]];
            if (graph[0].count(node) > 0) {
                is_there_duplicate_edges = true;
            } else {
                graph[0].insert(node);
                graph[node].insert(0);
            }
        } else {
            int first_node = prime_index[primes_inside[0]];
            int second_node = prime_index[primes_inside[1]];
            if (graph[first_node].count(second_node) > 0) {
                is_there_duplicate_edges = true;
            } else {
                graph[first_node].insert(second_node);
                graph[second_node].insert(first_node);
            }
        }
    }
    if (is_there_duplicate_edges) {
        std::cout << 2 << std::endl;
        return 0;
    }
    int min_cycle = std::numeric_limits<int>::max();
    for (size_t node = 0; node < graph.size() && (node == 0 || primes[node - 1] <= 1000); ++node) {
        if (graph[node].size() > 0) {
            std::optional<int> current_min_cycle = FindMinimalCycle(node, graph, max_bfs_depth);
            if (current_min_cycle.has_value()) {
                min_cycle = std::min(min_cycle, current_min_cycle.value());
            }
        }
    }
    if (min_cycle == std::numeric_limits<int>::max()) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << min_cycle << std::endl;
    }
    return 0;
}
