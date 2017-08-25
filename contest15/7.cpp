#include <vector>
#include <iostream>

struct Linear {
    long long int a = 0;
    long long int b = 0;

    Linear& operator+=(const Linear& other) {
        a += other.a;
        b += other.b;
        return *this;
    }
    Linear& operator-=(const Linear& other) {
        a -= other.a;
        b -= other.b;
        return *this;
    }

    Linear operator-(const Linear& other) const {
        Linear new_object(*this);
        new_object -= other;
        return new_object;
    }

    Linear operator+(const Linear& other) const {
        Linear new_object(*this);
        new_object += other;
        return new_object;
    }
};

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
    PersistentSegmentTree& InitalizeTreeRecursive(Node* parent, const TCoord& left, const TCoord& right) {
        if (right > left + 1) {
            TCoord middle = (left + right) / 2;
            parent->left_node = new Node{left, middle};
            parent->right_node = new Node{middle, right};
            InitalizeTreeRecursive(parent->left_node, left, middle);
            InitalizeTreeRecursive(parent->right_node, middle, right);
        }
        return *this;
    }
    PersistentSegmentTree(const TCoord& left, const TCoord& right) {
        versioned_roots.push_back(new Node{left, right});
        InitalizeTreeRecursive(versioned_roots[0], left, right);
    }
    Node* CloneNodeAddingValue(Node* node, const TValue& value) {
        return new Node{node->left, node->right, node->value + value};
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
            TCoord middle = (parent->left + parent->right) / 2;
            if (coord >= middle) {
//                std::cout << "Summing from segment" << *parent->left_node << std::endl;
                return GetPrefixSumRecursive(parent->right_node, coord) + parent->left_node->value;
            } else {
                return GetPrefixSumRecursive(parent->left_node, coord);
            }
        } else if (coord == parent->right && parent->right == parent->left + 1) {
//            std::cout << "Summing from segment" << *parent << std::endl;
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
};

int main() {
    PersistentSegmentTree<long long int, Linear> tree(0, 200001);
    int n;
    std::cin >> n;
    std::vector<long long int> constant_prefix_sums(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        long long int x1, x2, y1, y2, a, b;
        std::cin >> x1 >> x2 >> y1 >> a >> b >> y2;
        tree.Update(x1, {a, b - y1});
        tree.Update(x2, {-a, y2 - b});
        constant_prefix_sums[i + 1] = y1;
        constant_prefix_sums[i + 1] += constant_prefix_sums[i];
    }
    int m;
    std::cin >> m;
    long long int last = 0;
    for (int i = 0; i < m; ++i) {
        int l, r;
        long long int x;
        std::cin >> l >> r >> x;
        --l;
        --r;
        x += last;
        x %= 1000000000;
        long long int initial_constant = constant_prefix_sums[r + 1] - constant_prefix_sums[l];
        Linear first_linear = tree.GetPrefixSum(2 * r + 2, x);
//        std::cout << "Done first_linear\n";
        Linear second_linear = tree.GetPrefixSum(2 * l, x);
        Linear linear = first_linear - second_linear;
        linear.b += initial_constant;
        last = linear.a * x + linear.b;
        std::cout << last << std::endl;
    }
    return 0;
}
