#include <iostream>
#include <vector>
#include <tuple>

struct VirtualNode {
    bool exists = false;
    long long int index = 0;

    bool operator==(const VirtualNode& node) const {
        return std::forward_as_tuple(exists, index) == std::forward_as_tuple(node.exists, node.index);
    }
};

template<typename T>
struct Node {
    T value;
    long long int left_subtree_size = 0;
    long long int right_subtree_size = 0;
    VirtualNode left_node;
    VirtualNode right_node;
    VirtualNode parent_node;
};

template<typename T>
class SplayTree {
    long long int GetSubTreeSize(const VirtualNode& node) {
        if (node.exists) {
            return nodes[node.index].left_subtree_size + 1 + nodes[node.index].right_subtree_size;
        } else {
            return 0;
        }
    }

    void SetLeftSubTreeSize(const VirtualNode& node, const long long int subtree_size) {
        if (node.exists) {
            nodes[node.index].left_subtree_size = subtree_size;
        }
    }

    void SetRightSubTreeSize(const VirtualNode& node, const long long int subtree_size) {
        if (node.exists) {
            nodes[node.index].right_subtree_size = subtree_size;
        }
    }

    void ConnectParentToLeft(const VirtualNode& parent, const VirtualNode& left) {
        SetLeftSubTreeSize(parent, GetSubTreeSize(left));
        if (parent.exists) {
            nodes[parent.index].left_node = left;
        }
        if (left.exists) {
            nodes[left.index].parent_node = parent;
        }
    }

    void ConnectParentToRight(const VirtualNode& parent, const VirtualNode& right) {
        SetRightSubTreeSize(parent, GetSubTreeSize(right));
        if (parent.exists) {
            nodes[parent.index].right_node = right;
        }
        if (right.exists) {
            nodes[right.index].parent_node = parent;
        }
    }

    void DisconnectParentFromLeft(const VirtualNode& parent, const VirtualNode& left) {
        SetLeftSubTreeSize(parent, 0);
        if (parent.exists) {
            nodes[parent.index].left_node = {};
        }
        if (left.exists) {
            nodes[left.index].parent_node = {};
        }
    }

    void DisconnectParentFromRight(const VirtualNode& parent, const VirtualNode& right) {
        SetRightSubTreeSize(parent, 0);
        if (parent.exists) {
            nodes[parent.index].right_node = {};
        }
        if (right.exists) {
            nodes[right.index].parent_node = {};
        }
    }

    VirtualNode GetParentVirtualNode(const VirtualNode& node) {
        if (node.exists) {
            return nodes[node.index].parent_node;
        } else {
            return {};
        }
    }

    VirtualNode GetLeftVirtualNode(const VirtualNode& node) const {
        if (node.exists) {
            return nodes[node.index].left_node;
        } else {
            return {};
        }
    }

    VirtualNode GetRightVirtualNode(const VirtualNode& node) const {
        if (node.exists) {
            return nodes[node.index].right_node;
        } else {
            return {};
        }
    }

    void RotateRight(const VirtualNode& node) {
        VirtualNode d = node;
        VirtualNode x = GetParentVirtualNode(d);
        VirtualNode b = GetLeftVirtualNode(d);
//        VirtualNode e = GetRightVirtualNode(d);
//        VirtualNode a = GetLeftVirtualNode(b);
        VirtualNode c = GetRightVirtualNode(b);
        DisconnectParentFromLeft(d, b);
        DisconnectParentFromRight(b, c);
        bool is_parent_left = x.exists && nodes[x.index].left_node == d;
        if (is_parent_left) {
            DisconnectParentFromLeft(x, d);
        } else {
            DisconnectParentFromRight(x, d);
        }
        ConnectParentToLeft(d, c);
        ConnectParentToRight(b, d);
        if (is_parent_left) {
            ConnectParentToLeft(x, b);
        } else {
            ConnectParentToRight(x, b);
        }
    }

    void RotateLeft(const VirtualNode& node) {
        VirtualNode b = node;
        VirtualNode x = GetParentVirtualNode(b);
//        VirtualNode a = GetLeftVirtualNode(b);
        VirtualNode d = GetRightVirtualNode(b);
        VirtualNode c = GetLeftVirtualNode(d);
//        VirtualNode e = GetRightVirtualNode(d);
        bool is_parent_left = x.exists && nodes[x.index].left_node == b;
        DisconnectParentFromRight(b, d);
        DisconnectParentFromLeft(d, c);
        if (is_parent_left) {
            DisconnectParentFromLeft(x, b);
        } else {
            DisconnectParentFromRight(x, b);
        }
        ConnectParentToRight(b, c);
        ConnectParentToLeft(d, b);
        if (is_parent_left) {
            ConnectParentToLeft(x, d);
        } else {
            ConnectParentToRight(x, d);
        }
    }

    bool RotateUp(const VirtualNode& node) {
        VirtualNode parent = nodes[node.index].parent_node;
        if (parent.exists) {
            if (nodes[parent.index].left_node == node) {
                RotateRight(parent);
            } else {
                RotateLeft(parent);
            }
            return true;
        } else {
            return false;
        }
    }

    void Splay(const VirtualNode& node) {
        while (RotateUp(node)) {
        }
        root_index = node.index;
    }

    std::tuple<VirtualNode, VirtualNode> FindPrevAndCurNode(const T& value) {
        VirtualNode current_node{true, root_index};
        VirtualNode prev_node;
        while (current_node.exists && (nodes[current_node.index].value < value || value < nodes[current_node.index].value)) {
            prev_node = current_node;
            if (nodes[current_node.index].value < value) {
                current_node = GetRightVirtualNode(current_node);
            } else {
                current_node = GetLeftVirtualNode(current_node);
            }
        }
        return std::make_tuple(prev_node, current_node);
    }

    void PrintTreeRecursive(const VirtualNode& node, const long long int spaces, const char symbol) const {
        if (node.exists) {
            for (long long int i = 0; i < spaces; ++i) {
                std::cout << " ";
            }
            std::cout << symbol << "Node(index = " << node.index << ", " << nodes[node.index].value << ", left_size = "
                << nodes[node.index].left_subtree_size << ", right_size = " << nodes[node.index].right_subtree_size << ")" << std::endl;
            PrintTreeRecursive(GetLeftVirtualNode(node), spaces + 2, 'L');
            PrintTreeRecursive(GetRightVirtualNode(node), spaces + 2, 'R');
        }
    }

    void PrintTree() const {
        PrintTreeRecursive({max_index > 0, root_index}, 0, ':');
    }
public:
    SplayTree(const long long int max_size)
        : nodes(max_size)
        , max_index(0)
        , root_index(0)
    {}

    friend std::ostream& operator<<(std::ostream& out, const SplayTree& tree) {
        tree.PrintTree();
        return out;
    }

    void Insert(const T& value) {
        if (max_index == 0) {
            nodes[max_index++].value = value;
        } else {
            VirtualNode prev_node, current_node;
            std::tie(prev_node, current_node) = FindPrevAndCurNode(value);

            if (!(nodes[current_node.index].value < value) && !(value < nodes[current_node.index].value)) {
                // Do nothing
            } else {
                VirtualNode new_node{true, max_index++};
                nodes[new_node.index] = {value, 0, 0, {}, {}, {}};
                if (nodes[prev_node.index].value < value) {
                    ConnectParentToRight(prev_node, new_node);
                } else {
                    ConnectParentToLeft(prev_node, new_node);
                }
                Splay(new_node);
            }
        }
    }

    long long int GetMoreCount(const T& value) {
        if (max_index == 0) {
            return 0;
        } else {
            VirtualNode prev_node, current_node;
            std::tie(prev_node, current_node) = FindPrevAndCurNode(value);
            if (!(nodes[current_node.index].value < value) && !(value < nodes[current_node.index].value)) {
                Splay(current_node);
                return 1 + nodes[current_node.index].right_subtree_size;
            } else {
                Splay(prev_node);
                if (nodes[prev_node.index].value < value) {
                    return nodes[prev_node.index].right_subtree_size;
                } else {
                    return nodes[prev_node.index].right_subtree_size + 1ll;
                }
            }
        }
    }
private:
    std::vector<Node<T>> nodes;
    long long int max_index;
    long long int root_index;
};
