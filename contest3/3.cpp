#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void dfs(
    std::vector<std::vector< long long int > >& edges,
    std::vector<long long int>& nodes,
    std::vector<bool>& is_used,
    std::vector<long long int>& parent,
    const long long int node,
    const long long int depth
) {
    if (!is_used[node]) {
        nodes.push_back(node);
        is_used[node] = true;
        for (auto& neigbour : edges[node]) {
            if (!is_used[neigbour]) {
                parent[neigbour] = node;
            }
            dfs(edges, nodes, is_used, parent, neigbour, depth + 1);
        }
    }
}

int main () {
    long long int n,k;
    std::cin >> n >> k;
    std::vector<std::vector< long long int > > edges(n);
    for (size_t i = 0; i < n - 1; ++i) {
        long long int from, to;
        std::cin >> from >> to;
        --from;
        --to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    std::vector<long long int> nodes;
    std::vector<bool> is_used(n, false);
    std::vector<long long int> parent(n, -1);
    dfs(edges, nodes, is_used, parent, 0, 0);

    std::vector<long long int> modulo_root_paths(n * k, 0);
    std::vector<long long int> modulo_subtree_paths(n * k, 0);
    std::vector<long long int> subtree_size(n, 1);
    long long int paths_sum = 0;

    for (size_t i = 0; i < n; ++i) {
        modulo_root_paths[k * i] = 1;
        modulo_subtree_paths[k * i] = 1;
    }

    std::reverse(nodes.begin(), nodes.end());
    std::vector<long long int> sum(k, 0);
    std::vector<long long int> cross_sums(k * k, 0);

    for (auto& node: nodes) {
        for (size_t i = 0; i < k; ++i) {
            sum[i] = 0;
            for (auto& child: edges[node]) {
                if (child != parent[node]) {
                    sum[i] += modulo_root_paths[k * child + i];
                }
            }
            for (size_t j = 0; j < k; ++j) {
                cross_sums[i * k + j] = 0;
                for (auto& child: edges[node]) {
                    if (child != parent[node]) {
                        cross_sums[i * k + j] += modulo_root_paths[k * child + i] * modulo_root_paths[k * child + j];
                    }
                }
            }
        }

        for (size_t i = 0; i < k; ++i) {
            for (size_t j = i; j < k; ++j) {
                if (i == j) {
                    modulo_subtree_paths[k * node + ((i + j + 2) % k)] += (sum[i] * sum[j] - cross_sums[i * k + j]) / 2;
                } else {
                    modulo_subtree_paths[k * node + ((i + j + 2) % k)] += (sum[i] * sum[j] - cross_sums[i * k + j]);
                }
            }
        }

        for (auto& child: edges[node]) {
            if (child != parent[node]) {
                for (size_t i = 0; i < k; ++i) {
                    modulo_root_paths[k * node + i] += modulo_root_paths[k * child + ((i + k - 1) % k)];
                    modulo_subtree_paths[k * node + i] += modulo_subtree_paths[k * child + i];
                    modulo_subtree_paths[k * node + i] += modulo_root_paths[k * child + ((i + k - 1) % k)];
                }
                subtree_size[node] += subtree_size[child];
//                for (auto& other_node: edges[node]) {
//                    if (child > other_node && other_node != parent[node]) {
//                        for (size_t i = 0; i < k; ++i) {
//                            for (size_t j = 0; j < k; ++j) {
//                                modulo_subtree_paths[k * node + ((i + j + 2) % k)] += (
//                                    modulo_root_paths[k * child + i]
//                                    * modulo_root_paths[k * other_node + j]
//                                );
//                            }
//                        }
//                    }
//                }
                paths_sum += (n - subtree_size[child]) * subtree_size[child];
            }
        }
    }
    for (size_t i = 1; i < k; ++i) {
        paths_sum += (k - i) * modulo_subtree_paths[i];
    }

    paths_sum /= k;
    std::cout << paths_sum << std::endl;

    return 0;
}
