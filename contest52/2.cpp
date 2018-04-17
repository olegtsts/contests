#include <iostream>
#include <vector>

struct ChildrenOrder {
    bool is_possible = false;
    std::vector<int> children_order = {};
};

void DFS(
    const int current_node,
    const std::vector<std::vector<int>>& children,
    std::vector<ChildrenOrder>& even_order,
    std::vector<ChildrenOrder>& odd_order
) {
    std::vector<int> only_odd_children;
    int index_of_dual_child = -1;
    std::vector<int> even_children;
    for (auto& child: children[current_node]) {
        DFS(child, children, even_order, odd_order);
        if (even_order[child].is_possible) {
            even_children.push_back(child);
            if (odd_order[child].is_possible) {
                index_of_dual_child = child;
            } else {
                // Nothing
            }
        } else {
            if (odd_order[child].is_possible) {
                only_odd_children.push_back(child);
            } else {
                // Impossible to do anything
                return;
            }
        }
    }
    if (children[current_node].size() == 0) {
        even_order[current_node] = {true, {current_node}};
        return;
    }
    int remained = static_cast<int>(children[current_node].size()) - static_cast<int>(only_odd_children.size());
    //Even possibility
    if (remained % 2 == 0 || index_of_dual_child >= 0) {
        even_order[current_node].is_possible = true;
        even_order[current_node].children_order = only_odd_children;
        if (remained % 2 == 0) {
            even_order[current_node].children_order.push_back(current_node);
            std::copy(even_children.begin(), even_children.end(), std::back_inserter(even_order[current_node].children_order));
        } else {
            even_order[current_node].children_order.push_back(index_of_dual_child);
            even_order[current_node].children_order.push_back(current_node);
            for (auto& child: even_children) {
                if (child != index_of_dual_child) {
                    even_order[current_node].children_order.push_back(child);
                }
            }
        }
    }

    //Odd possibility
    if (remained % 2 == 1 || index_of_dual_child >= 0) {
        odd_order[current_node].is_possible = true;
        odd_order[current_node].children_order = only_odd_children;
        if (remained % 2 == 1) {
            odd_order[current_node].children_order.push_back(current_node);
            std::copy(even_children.begin(), even_children.end(), std::back_inserter(odd_order[current_node].children_order));
        } else {
            odd_order[current_node].children_order.push_back(index_of_dual_child);
            odd_order[current_node].children_order.push_back(current_node);
            for (auto& child: even_children) {
                if (child != index_of_dual_child) {
                    odd_order[current_node].children_order.push_back(child);
                }
            }
        }
    }
}

void AnotherDFS(
    const int current_node,
    std::vector<ChildrenOrder>& even_order,
    std::vector<ChildrenOrder>& odd_odder,
    std::vector<int>& result_traversal,
    const bool is_parent_deleted
) {
    ChildrenOrder * order_to_use;
    if (is_parent_deleted) {
        order_to_use = &even_order[current_node];
    } else {
        order_to_use = &odd_odder[current_node];
    }
    bool is_current_node_deleted = false;
    for (auto& node: order_to_use->children_order) {
        if (node == current_node) {
            result_traversal.push_back(current_node);
            is_current_node_deleted = true;
        } else {
            AnotherDFS(node, even_order, odd_odder, result_traversal, is_current_node_deleted);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> children(n);
    int root_node = -1;
    for (int i = 0; i < n; ++i) {
        int child_node = i;
        int parent_node;
        std::cin >> parent_node;
        --parent_node;
        if (parent_node >= 0) {
            children[parent_node].push_back(child_node);
        } else {
            root_node = child_node;
        }
    }
    std::vector<ChildrenOrder> even_order(n, {false, {}});
    std::vector<ChildrenOrder> odd_order(n, {false, {}});
    DFS(root_node, children, even_order, odd_order);
    if (even_order[root_node].is_possible) {
        std::cout << "YES\n";
        std::vector<int> result_traversal;
        AnotherDFS(root_node, even_order, odd_order, result_traversal, true);
        for (auto& node: result_traversal) {
            std::cout << node + 1 << std::endl;
        }
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
