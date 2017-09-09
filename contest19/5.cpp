#include <cassert>
#include <vector>
#include <iostream>

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

long long int GetPointsInSqare(
    PersistentSegmentTree<int, int>& segment_tree,
    int l,
    int d,
    int r,
    int u
) {
    return static_cast<long long int>(segment_tree.GetPrefixSum(r, u) - segment_tree.GetPrefixSum(l, u) - segment_tree.GetPrefixSum(r, d) + segment_tree.GetPrefixSum(l, d));
}

long long int GetRectCount(const long long int k) {
    return k * (k - 1) / 2;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n,q;
    std::cin >> n >> q;
    PersistentSegmentTree<int, int> segment_tree(0, 200001, n + 1);
    for (int i = 0; i < n; ++i) {
        int p;
        std::cin >> p;
        --p;
        segment_tree.Update(p, 1);
    }

    for (int i = 0; i < q; ++i) {
        int l, d, r, u;
        std::cin >> l >> d >> r >> u;
        --l;
        --d;
        --r;
        --u;
        long long int l_d = segment_tree.GetPrefixSum(l, d);
        long long int r_d = segment_tree.GetPrefixSum(r + 1, d);
        long long int n_d = segment_tree.GetPrefixSum(n, d);
        long long int l_u = segment_tree.GetPrefixSum(l, u + 1);
        long long int r_u = segment_tree.GetPrefixSum(r + 1, u + 1);
        long long int n_u = segment_tree.GetPrefixSum(n, u + 1);
        long long int l_n = segment_tree.GetPrefixSum(l, n);
        long long int r_n = segment_tree.GetPrefixSum(r + 1, n);
        std::cout << (
            GetRectCount(n)
            - GetRectCount(n_d)
            - GetRectCount(l_n)
            - GetRectCount(n - n_u)
            - GetRectCount(n - r_n)
            + GetRectCount(l_d)
            + GetRectCount(l_n - l_u)
            + GetRectCount(n_d - r_d)
            + GetRectCount(n - r_n - n_u + r_u)
        ) << std::endl;
    }

    return 0;
}
