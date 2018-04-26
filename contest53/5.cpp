#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <unordered_map>

const size_t NO_NEIGHBOUR = std::numeric_limits<size_t>::max();

class PrefixTree {
    struct Node {
        std::vector<size_t> neighbours;
        bool is_terminal;
        Node()
            : neighbours('z' - 'a' + 1, NO_NEIGHBOUR),
              is_terminal(false)
        {}

        bool isThereChild(const char ch) const {
            return neighbours[ch - 'a'] != NO_NEIGHBOUR;
        }

        size_t getChildIndex(const char ch) const {
            return neighbours[ch - 'a'];
        }
    };

public:
    PrefixTree()
        : nodes(1),
          max_node_index(1)
    {
    }

    void AddWord(const std::string& word) {
        size_t current_index = 0;
        std::vector<size_t> path_from_root(1, 0);
        for (char symbol : word) {
            if (nodes[current_index].isThereChild(symbol)) {
                current_index = nodes[current_index].getChildIndex(symbol);
            } else {
                nodes[current_index].neighbours[symbol - 'a'] = max_node_index;
                nodes.push_back({});
                current_index = max_node_index;
                ++max_node_index;
            }
            path_from_root.push_back(current_index);
        }
        nodes[current_index].is_terminal = true;
    }

    struct LayerNodes {
        std::unordered_map<size_t, std::list<size_t>> layer_nodes;
        size_t max_layer;

        bool IsEmpty() const {
            return layer_nodes.empty();
        }
        void ChangeMaxLayer() {
            if (IsEmpty()) {
                return;
            }
            while (layer_nodes.count(max_layer) == 0) {
                --max_layer;
            }
        }
        void PopMaxLayerNode() {
            layer_nodes[max_layer].erase(layer_nodes[max_layer].begin());
            if (layer_nodes[max_layer].size() == 0) {
                layer_nodes.erase(max_layer);
                ChangeMaxLayer();
            }
        }
        void AddNode(size_t layer, size_t node) {
            bool is_empty_before = IsEmpty();
            if (layer_nodes.count(layer) == 0) {
                layer_nodes[layer] = {};
            }
            layer_nodes[layer].insert(layer_nodes[layer].end(), node);
            if (is_empty_before || max_layer < layer) {
                max_layer = layer;
            }
        }
        void MergeWithAnother(LayerNodes && another_layer_nodes) {
            if (!IsEmpty() || !another_layer_nodes.IsEmpty()) {
                max_layer = std::max(IsEmpty() ? 0 : max_layer, another_layer_nodes.IsEmpty() ? 0 : another_layer_nodes.max_layer);
            }
            for (auto input_pair: another_layer_nodes.layer_nodes) {
                auto new_layer = input_pair.first;
                auto & contained_list = input_pair.second;
                if (layer_nodes.count(new_layer) == 0) {
                    layer_nodes[new_layer] = {};
                }
                layer_nodes[new_layer].splice(layer_nodes[new_layer].end(), std::move(contained_list));
            }
        }

        size_t GetTotalSize() const {
            size_t result = 0;
            for (auto input_pair: layer_nodes) {
                result += input_pair.first * input_pair.second.size();
            }
            return result;
        }
    };

    LayerNodes GetLayerNodesRecursive(const size_t current_node, const size_t depth) const {
        LayerNodes layer_nodes;
        if (nodes[current_node].is_terminal) {
            layer_nodes.AddNode(depth, current_node);
        }
        for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
            if (nodes[current_node].isThereChild(symbol)) {
                size_t child = nodes[current_node].getChildIndex(symbol);
                LayerNodes child_layer_nodes = GetLayerNodesRecursive(child, depth + 1);
                layer_nodes.MergeWithAnother(std::move(child_layer_nodes));
            }
        }
        if (current_node != 0 && !nodes[current_node].is_terminal && !layer_nodes.IsEmpty()) {
            layer_nodes.PopMaxLayerNode();
            layer_nodes.AddNode(depth, current_node);
        }
        return layer_nodes;
    }

    size_t GetShortenedSize() const {
        return GetLayerNodesRecursive(0, 0).GetTotalSize();
    }
private:
    std::vector<Node> nodes;
    size_t max_node_index = 0;
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    PrefixTree prefix_tree;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        prefix_tree.AddWord(word);
    }
    std::cout << prefix_tree.GetShortenedSize() << std::endl;
    return 0;
}
