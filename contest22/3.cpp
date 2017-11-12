#include <iostream>
#include <vector>

int main() {
    size_t n;
    std::cin >> n;
    std::vector<size_t> last_seen(200001, 0);
    std::vector<size_t> nodes(1, 0);
    size_t next_node_index = 1;
    for (size_t i = 0; i < n; ++i) {
        size_t cur_time;
        std::cin >> cur_time;
        size_t node;
        if (last_seen[nodes[cur_time]] == cur_time) {
            node = nodes[cur_time];
        } else {
            node = next_node_index++;
        }
        nodes.push_back(node);
        last_seen[node] = i + 1;
    }
    std::cout << next_node_index << std::endl;
    return 0;
}
