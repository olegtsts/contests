#include <vector>
#include <iostream>
#include <cassert>

class MinXorTree {
private:
    struct MinXorNode {
        bool is_final = false;
        int counter = 0;
        size_t left = 0;
        size_t right = 0;
        long long int number = 0;
        int bit = -1;
    };
public:
    MinXorTree()
        : nodes(16000000)
        , max_index(1)
    {
    }

    void Insert(const long long int number) {
        size_t current_node = 0;
        for (int bit = 30; bit >=0; --bit) {
            ++nodes[current_node].counter;
            nodes[current_node].bit = bit;
            if (number & (1ll << bit)) {
                if (nodes[current_node].right == 0) {
                    nodes[current_node].right = max_index++;
                }
                current_node = nodes[current_node].right;
            } else {
                if (nodes[current_node].left == 0) {
                    nodes[current_node].left = max_index++;
                }
                current_node = nodes[current_node].left;
            }
            if (bit == 0) {
                ++nodes[current_node].counter;
                nodes[current_node].number = number;
            }
        }
    }
    bool RecursiveRemove(const size_t current_node, const long long int number, const int bit) {
        if (bit >= 0) {
            if (number & (1ll << bit)) {
                if (RecursiveRemove(nodes[current_node].right, number, bit - 1)) {
                    nodes[current_node].right = 0;
                }
            } else {
                if (RecursiveRemove(nodes[current_node].left, number, bit - 1)) {
                    nodes[current_node].left = 0;
                }
            }
        }
        if (--nodes[current_node].counter == 0) {
            nodes[current_node] = {};
            return true;
        } else {
            return false;
        }
    }
    void Remove(const long long int number) {
        RecursiveRemove(0, number, 30);
    }
    long long int GetMinXor(const long long int target) {
        size_t current_node = 0;
        for (int bit = 30; bit >= 0; --bit) {
            if (target & (1ll << bit)) {
                if (nodes[current_node].right) {
                    current_node = nodes[current_node].right;
                } else {
                    current_node = nodes[current_node].left;
                }
            } else {
                if (nodes[current_node].left) {
                    current_node = nodes[current_node].left;
                } else {
                    current_node = nodes[current_node].right;
                }
            }
            assert(current_node != 0);
        }
        return nodes[current_node].number;
    }
private:
    std::vector<MinXorNode> nodes;
    size_t max_index;
};
int main() {
    int n;
    std::cin >> n;
    std::vector<long long int> a(n);
    std::vector<long long int> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }
    MinXorTree tree;
    for (int i = 0; i < n; ++i) {
        tree.Insert(p[i]);
    }
    for (int i = 0; i < n; ++i) {
        long long int number = tree.GetMinXor(a[i]);
        std::cout << (number ^ a[i]) << " ";
        tree.Remove(number);
    }
    std::cout << std::endl;
    return 0;
}
