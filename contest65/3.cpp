#include <iostream>
#include <vector>

struct NodeInfo {
    int subtree_size;
    int parent;
    int leaf;
};

void DFS(int n, const std::vector<std::vector<int>>& edges, std::vector<bool>& is_visited, std::vector<NodeInfo>& infos, int current_node, int parent_node) {
    if (is_visited[current_node]) {
        return;
    }
    infos[current_node].subtree_size = 1;
    infos[current_node].parent = parent_node;
    infos[current_node].leaf = current_node;
    for (int another_node : edges[current_node]) {
        if (another_node != parent_node) {
            DFS(n, edges, is_visited, infos, another_node, current_node);
            infos[current_node].subtree_size += infos[another_node].subtree_size;
            infos[current_node].leaf = infos[another_node].leaf;
        }
    }
}

void SolveTest() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> edges(n);
    for (int i = 0; i + 1 < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x;
        --y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    std::vector<NodeInfo> infos(n);
    std::vector<bool> is_visited(n, false);
    DFS(n, edges, is_visited, infos, 0, -1);
    for (int node = 0; node < n; ++node) {
        if (infos[node].subtree_size * 2 == n) {
            std::cout << infos[node].leaf + 1 << " " << infos[infos[node].leaf].parent + 1 << std::endl <<
                infos[node].parent + 1 << " " << infos[node].leaf + 1 << std::endl;
            return;
        }
    }
    std::cout << 1 + 1 << " " << infos[1].parent + 1 << std::endl << 1 + 1 << " " << infos[1].parent + 1 << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        SolveTest();
    }
    return 0;
}
