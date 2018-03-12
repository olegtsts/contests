#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class PrefixTree {
private:
    struct Vertex {
        std::vector<size_t> other_indices;
        size_t count_of_edges;
        bool is_terminated;
        Vertex()
            : other_indices(26, 0)
            , count_of_edges(0)
            , is_terminated(false)
        {}
    };
public:
    PrefixTree()
        : vertexes(1000002)
        , max_index(1)
    {
    }
    size_t AddWord(const std::string& word) {
        size_t current_index = 0;
        bool is_new_added = false;
        int last_index_with_one_edge = -1;
        for (size_t i = 0; i < word.size(); ++i) {
            auto symbol = word[i];
            auto& vertex = vertexes[current_index];
            if (vertex.other_indices[symbol - 'a'] > 0) {
                current_index = vertex.other_indices[symbol - 'a'];
            } else {
                is_new_added = true;
                size_t new_index = max_index;
                vertex.other_indices[symbol - 'a'] = new_index;
                ++vertex.count_of_edges;
                ++max_index;
                current_index = new_index;
            }
            if (vertex.count_of_edges == 1 && !vertex.is_terminated) {
                if (last_index_with_one_edge == -1) {
                    last_index_with_one_edge = i;
                }
            } else {
                last_index_with_one_edge = -1;
            }
        }
        vertexes[current_index].is_terminated = true;
        if (!is_new_added && vertexes[current_index].count_of_edges == 0) {
            if (last_index_with_one_edge == -1) {
                return word.size();
            } else {
                return std::max(last_index_with_one_edge, 1);
            }
        } else {
            return word.size();
        }
    }
private:
    std::vector<Vertex> vertexes;
    size_t max_index;
};
int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    PrefixTree prefix_tree;
    size_t total_points = 0;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        total_points += prefix_tree.AddWord(word);
    }
    std::cout << total_points << std::endl;
    return 0;
}
