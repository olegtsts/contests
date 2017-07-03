#include <iostream>
#include <vector>
#include <iomanip>

void dfs(
    std::vector<long double>& phases,
    std::vector<int>& edge_parent,
    std::vector<std::vector<std::pair<int, int> > >& edges,
    std::vector<bool>& is_used,
    const int current_node,
    const long double parent_phase,
    const int parent_node
) {
    if (!is_used[current_node]) {
        is_used[current_node] = true;
        long double initial_phase;
        int split = edges[current_node].size();
        if (parent_phase == -1) {
            initial_phase = 0;
        } else {
            initial_phase = (1 + parent_phase);
            if (initial_phase >= 2) {
                initial_phase -= 2;
            }
        }
        if (split > 0) {
            long double step = static_cast<long double>(2) / split;
            for (auto& pair: edges[current_node]) {
                auto next_node = pair.first;
                if (next_node != parent_node) {
                    auto edge_index = pair.second;
                    initial_phase += step;
                    if (initial_phase >= 2) {
                        initial_phase -= 2;
                    }
                    phases[edge_index] = initial_phase;
                    edge_parent[edge_index] = current_node;
                    dfs(phases, edge_parent, edges, is_used, next_node, initial_phase, current_node);
                }
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, int> > > edges(n);
    std::vector<std::pair<int, int> > plain_edges(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        a -= 1;
        b -= 1;
        edges[a].push_back(std::make_pair(b, i));
        edges[b].push_back(std::make_pair(a, i));
        plain_edges[i] = std::make_pair(a, b);
    }
    std::cout << std::setprecision(10);
    std::vector<long double> phases(n - 1, 0);
    std::vector<int> edge_parent(n - 1, 0);
    std::vector<bool> is_used(n, false);
    dfs(phases, edge_parent, edges, is_used, 0, -1, -1);
    std::cout << n - 1 << std::endl;
    for (int i = 0; i < n - 1; ++i) {
        std::cout << 1 << " " << (i + 1) << " ";
        long double phase = phases[i];
        int parent = edge_parent[i];
        int child;
        if (plain_edges[i].first == parent) {
            child = plain_edges[i].second;
        } else {
            child = plain_edges[i].first;
        }
        if (phase <= 1) {
            std::cout << parent + 1 << " " << child + 1 << " " << phase << std::endl;
        } else {
            std::cout << child + 1 << " " << parent + 1 << " " << phase - 1 << std::endl;
        }
    }
    return 0;
}
