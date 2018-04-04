#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

template <typename TCoord, typename TValue>
class PersistentSegmentTree {
private:
    struct Node {
        TCoord left = 0;
        TCoord right = 0;
        TValue value = {};

        Node* left_node = nullptr;
        Node* right_node = nullptr;
    };
public:
    Node* GetNewNode(const TCoord& left, const TCoord& right, const TValue& value) {
        assert(node_pool_index < node_pool.size());
        Node* node = &node_pool[node_pool_index++];
        node->left = left;
        node->right = right;
        node->value = value;
        return node;
    }

    PersistentSegmentTree& InitalizeTreeRecursive(Node* parent, const TCoord& left, const TCoord& right) {
        if (right > left + 1) {
            TCoord middle = (left + right) / 2;
            parent->left_node = GetNewNode(left, middle, {});
            parent->right_node = GetNewNode(middle, right, {});
            InitalizeTreeRecursive(parent->left_node, left, middle);
            InitalizeTreeRecursive(parent->right_node, middle, right);
        }
        return *this;
    }
    PersistentSegmentTree(const TCoord& left, const TCoord& right, const size_t versions_count)
    : node_pool(5000000), node_pool_index(0) {
        versioned_roots.reserve(versions_count);
        versioned_roots.push_back(GetNewNode(left, right, {}));
        InitalizeTreeRecursive(versioned_roots[0], left, right);
    }
    Node* CloneNodeAddingValue(Node* node, const TValue& value) {
        return GetNewNode(node->left, node->right, node->value + value);
    }
    PersistentSegmentTree& UpdateRecursive(Node* new_parent, Node* parent, const TCoord& coord, const TValue& value) {
        if (parent->right > parent->left + 1) {
            TCoord middle = (parent->left + parent->right) / 2;
            if (coord >= middle) {
                new_parent->left_node = parent->left_node;
                new_parent->right_node = CloneNodeAddingValue(parent->right_node, value);
                UpdateRecursive(new_parent->right_node, parent->right_node, coord, value);
            } else {
                new_parent->left_node = CloneNodeAddingValue(parent->left_node, value);
                new_parent->right_node = parent->right_node;
                UpdateRecursive(new_parent->left_node, parent->left_node, coord, value);
            }
        }
        return *this;
    }
    PersistentSegmentTree& Update(const TCoord& coord, const TValue& value) {
        Node* root = versioned_roots.back();
        Node* new_root = CloneNodeAddingValue(root, value);
        versioned_roots.push_back(new_root);
        UpdateRecursive(new_root, root, coord, value);
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& st, const Node& node) {
        st << "(" << node.left << "," << node.right << ")";
        return st;
    }
    TValue GetPrefixSumRecursive(Node* parent, const TCoord& coord) {
        if (parent->right > parent->left + 1) {
            if (coord >= parent->right) {
                return parent->value;
            }
            TCoord middle = (parent->left + parent->right) / 2;
            if (coord >= middle) {
                return GetPrefixSumRecursive(parent->right_node, coord) + parent->left_node->value;
            } else {
                return GetPrefixSumRecursive(parent->left_node, coord);
            }
        } else if (coord >= parent->right && parent->right == parent->left + 1) {
            return parent->value;
        } else {
            return {};
        }
    }
    TValue GetPrefixSum(const size_t version, const TCoord& coord) {
        return GetPrefixSumRecursive(versioned_roots[version], coord);
    }
private:
    std::vector<Node*> versioned_roots;
    std::vector<Node> node_pool;
    size_t node_pool_index;
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        a[i] = std::min(a[i], n);
    }
    PersistentSegmentTree<int, int> segment_tree(0, 200001, n + 1);
    long long int total = 0;
    for (int i = 0; i < n; ++i) {
        segment_tree.Update(a[i], 1);
    }
    for (int i = 0; i < n; ++i) {
        // i = i + 1 - 1
//        std::cout << "for i = " << i << ", a[i] = " << a[i] << " first = " << segment_tree.GetPrefixSum(std::min(a[i], i), 200001) << " and second = " <<  segment_tree.GetPrefixSum(std::min(a[i], i), i) << std::endl;
        total += segment_tree.GetPrefixSum(std::min(a[i], i), 200001) - segment_tree.GetPrefixSum(std::min(a[i], i), i + 1);
    }
    std::cout << total << std::endl;
    return 0;
}
