#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <set>
#include <tuple>
#include <utility>

struct Edge {
    int weight;
    int target;
};

struct NodeWithDistance {
    int distance;
    int node;

    bool operator<(const NodeWithDistance& other_node) const {
        return std::forward_as_tuple(distance, node) < std::forward_as_tuple(other_node.distance, other_node.node);
    }
};

void FindShortestPaths(
    const std::vector<std::vector<Edge>>& edges,
    int start_node,
    std::vector<int>& shortest_paths
) {
    shortest_paths[start_node] = 0;
    std::set<NodeWithDistance> remaining_nodes;
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        remaining_nodes.insert({shortest_paths[i], i});
    }
    while (remaining_nodes.size() > 0) {
        NodeWithDistance remaining_node = *remaining_nodes.begin();
        remaining_nodes.erase(remaining_node);
        for (Edge edge : edges[remaining_node.node]) {
            bool was_there_node = remaining_nodes.count({shortest_paths[edge.target], edge.target});
            if (was_there_node) {
                remaining_nodes.erase({shortest_paths[edge.target], edge.target});
            }
            shortest_paths[edge.target] = std::min(shortest_paths[edge.target], shortest_paths[remaining_node.node] + edge.weight);
            if (was_there_node) {
                remaining_nodes.insert({shortest_paths[edge.target], edge.target});
            }
        }
    }
}

int main() {
    int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<Edge>> edges(n);
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        --x;
        --y;
        edges[x].push_back({w, y});
        edges[y].push_back({w, x});
    }
    std::vector<std::pair<int, int>> ways(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> ways[i].first >> ways[i].second;
        --ways[i].first;
        --ways[i].second;
    }
    std::vector<std::vector<int>> shortest_paths(n, std::vector<int>(n, std::numeric_limits<int>::max()));
    for (int i = 0; i < n; ++i) {
        FindShortestPaths(edges, i, shortest_paths[i]);
    }
    int min_sum_of_paths = std::numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
        for (Edge edge : edges[i]) {
            int sum_of_paths = 0;
            for (const std::pair<int, int>& way : ways) {
                sum_of_paths += static_cast<int>(std::min(std::min(
                    shortest_paths[way.first][way.second],
                    shortest_paths[way.first][i] + shortest_paths[edge.target][way.second]),
                    shortest_paths[way.first][edge.target] + shortest_paths[i][way.second]));
            }
            min_sum_of_paths = std::min(min_sum_of_paths, sum_of_paths);
        }
    }
    std::cout << min_sum_of_paths << std::endl;
    return 0;
}

