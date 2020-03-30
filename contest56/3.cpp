#include <iostream>
#include <vector>
#include <utility>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> counters(n, 0);
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n - 1; ++i) {
        int first_node, second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        ++counters[first_node];
        ++counters[second_node];
        edges.push_back(std::make_pair(first_node, second_node));
    }
    std::vector<int> leave_edges;
    std::vector<int> non_leave_edges;
    for (int i = 0; i < n - 1; ++i) {
        auto [first_node, second_node] = edges[i];
        if (counters[first_node] == 1 || counters[second_node] == 1) {
            leave_edges.push_back(i);
        } else {
            non_leave_edges.push_back(i);
        }
    }
    int color = 0;
    std::vector<int> colors(n - 1);
    for (auto i : leave_edges) {
        colors[i] = color++;
    }
    for (auto i : non_leave_edges) {
        colors[i] = color++;
    }
    for (int i = 0; i < n - 1; ++i) {
        std::cout << colors[i] << std::endl;
    }
    return 0;
}
