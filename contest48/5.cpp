#include <iostream>
#include <vector>

const long long int MODULO = 1000000007;

struct DFSResult {
    long long int straight_even_paths = 0;
    long long int straight_odd_paths = 0;
    long long int straight_even_paths_sum = 0;
    long long int straight_odd_paths_sum = 0;
};

DFSResult DFS(
    const int node,
    const std::vector<std::vector<int>>& neighbours,
    std::vector<bool>& is_visited,
    const std::vector<long long int>& v,
    long long int& total_paths_sum
) {
    DFSResult total_result;
    total_result.straight_odd_paths += 1;
    total_result.straight_odd_paths %= MODULO;
    total_result.straight_odd_paths_sum += v[node];
    total_result.straight_odd_paths_sum %= MODULO;
    total_result.straight_odd_paths_sum += MODULO;
    total_result.straight_odd_paths_sum %= MODULO;
    total_paths_sum += v[node];
    total_paths_sum %= MODULO;
    total_paths_sum += MODULO;
    total_paths_sum %= MODULO;

    is_visited[node] = true;
    for (auto& neighbour: neighbours[node]) {
        if (!is_visited[neighbour]) {
            DFSResult local_result = DFS(neighbour, neighbours, is_visited, v, total_paths_sum);

            DFSResult new_total_result = total_result;
            new_total_result.straight_even_paths = ((total_result.straight_even_paths + local_result.straight_odd_paths) % MODULO + MODULO) % MODULO;
            new_total_result.straight_odd_paths = ((total_result.straight_odd_paths + local_result.straight_even_paths) % MODULO + MODULO) % MODULO;
            new_total_result.straight_even_paths_sum = (
                (total_result.straight_even_paths_sum + MODULO - local_result.straight_odd_paths_sum + v[node] * local_result.straight_odd_paths) % MODULO + MODULO
            ) % MODULO;
            new_total_result.straight_odd_paths_sum = (
                (total_result.straight_odd_paths_sum + MODULO - local_result.straight_even_paths_sum + v[node] * local_result.straight_even_paths) % MODULO + MODULO
            ) % MODULO;
            long long int addon = (
                (total_result.straight_even_paths * local_result.straight_odd_paths_sum * 2 % MODULO)
                 + (-total_result.straight_even_paths_sum * local_result.straight_odd_paths * 2 % MODULO)
                 + (-total_result.straight_odd_paths * local_result.straight_even_paths_sum * 2 % MODULO)
                 + (total_result.straight_odd_paths_sum * local_result.straight_even_paths * 2 % MODULO)
            ) % MODULO;
            total_paths_sum += addon;
            total_paths_sum += MODULO;
            total_paths_sum %= MODULO;
            total_result = new_total_result;
        }
    }
    return total_result;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<long long int> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    std::vector<std::vector<int>> neighbours(n);
    for (int i = 0; i + 1 < n; ++i) {
        int first_node,second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        neighbours[first_node].push_back(second_node);
        neighbours[second_node].push_back(first_node);
    }
    std::vector<bool> is_visited(n, false);
    long long int total_paths_sum = 0;
    DFS(0, neighbours, is_visited, v, total_paths_sum);
    std::cout << total_paths_sum << std::endl;
    return 0;
}
