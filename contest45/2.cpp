#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

class DSU {
public:
    DSU(const long long int n)
        : parent(n)
    {
        for (long long int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    long long int GetParent(const long long int index) {
        if (index == parent[index]) {
            return index;
        } else {
            parent[index] = GetParent(parent[index]);
            return parent[index];
        }
    }

    void Join(const long long int first_index, const long long int second_index) {
        parent[GetParent(first_index)] = GetParent(second_index);
    }
private:
    std::vector<long long int> parent;
};

int main() {
    std::ios::sync_with_stdio(false);
    long long int n,m,k;
    std::cin >> n >> k >> m;
    std::unordered_map<std::string, long long int> word_indexes;
    for (long long int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        word_indexes[word] = i;
    }
    std::vector<long long int> costs(n);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> costs[i];
    }
    DSU dsu(n);
    for (long long int i = 0; i < k; ++i) {
        long long int group_size;
        std::cin >> group_size;
        long long int first_word_index;
        std::cin >> first_word_index;
        --first_word_index;
        long long int min_cost = costs[first_word_index];
        for (long long int j = 1; j < group_size; ++j) {
            long long int word_index;
            std::cin >> word_index;
            --word_index;
            dsu.Join(first_word_index, word_index);
            min_cost = std::min(min_cost, costs[word_index]);
        }
        costs[dsu.GetParent(first_word_index)] = min_cost;
    }
    long long int total_score = 0;
    for (long long int i = 0; i < m; ++i) {
        std::string message_word;
        std::cin >> message_word;
        long long int word_index = word_indexes[message_word];
        total_score += costs[dsu.GetParent(word_index)];
    }
    std::cout << total_score << std::endl;
    return 0;
}
