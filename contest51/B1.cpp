#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> counts(n, 0);
    for (int i = 0; i + 1 < n; ++i) {
        int first_node, second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        ++counts[first_node];
        ++counts[second_node];
    }
    int count_of_leaves = 0;
    for (int i = 0; i < n; ++i) {
        if (counts[i] == 1) {
            ++count_of_leaves;
        }
    }
    std::cout << count_of_leaves << std::endl;
    return 0;
}
