#include <iostream>
#include <vector>
#include <utility>
#include <set>

struct Neighbour {
    int index;
    long long int cost;
};

void RelaxCostsDFS(
    std::vector<std::vector<Neighbour>> neighbours,
    std::vector<long long int>& costs,
    const int index
) {
    for (auto& neighbour: neighbours[index]) {
        if (neighbour.cost * 2 + costs[index] < costs[neighbour.index]) {
            costs[neighbour.index] = neighbour.cost * 2 + costs[index];
            RelaxCostsDFS(neighbours, costs, neighbour.index);
        }
    }
}


int main() {
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<std::vector<Neighbour>> neighbours(n);
    for (int i = 0; i < m; ++i) {
        int v,u;
        long long int w;
        std::cin >> v >> u >> w;
        --v;
        --u;
        neighbours[v].push_back({u, w});
        neighbours[u].push_back({v, w});
    }
    std::vector<long long int> costs(n);
    std::set<std::pair<long long int, int>> costs_indices;
    for (int i = 0; i < n; ++i) {
        std::cin >> costs[i];
        costs_indices.insert({costs[i], i});
    }
    while (costs_indices.size() > 0) {
        auto cur_pair = *costs_indices.begin();
        int index = cur_pair.second;
        costs_indices.erase(cur_pair);
        for (auto& neighbour: neighbours[index]) {
            if (costs[neighbour.index] > costs[index] + 2 * neighbour.cost) {
                costs_indices.erase({costs[neighbour.index], neighbour.index});
                costs[neighbour.index] = costs[index] + 2 * neighbour.cost;
                costs_indices.insert({costs[neighbour.index], neighbour.index});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << costs[i];
        if (i + 1 < n) {
            std::cout << " ";
        }
    }
    return 0;
}
