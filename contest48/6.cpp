#include <set>
#include <tuple>
#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

struct Element {
    long long int w;
    long long int l;

    bool operator<(const Element& other) const {
        return std::forward_as_tuple(w, l) < std::forward_as_tuple(other.w, other.l);
    }
};

struct BiSet {
    void Insert(const long long int new_w, const long long int new_l) {
        auto it = elements.lower_bound({new_w, new_l});
        if (it != elements.begin()) {
            auto prev_it = it;
            --prev_it;
            if (prev_it->l >= new_l) {
                return;
            }
        }
        std::vector<Element> elements_to_delete;
        while (it != elements.end() && it->l <= new_l) {
            elements_to_delete.push_back(*it);
            ++it;
        }
        for (auto& element_to_delete: elements_to_delete) {
            elements.erase(element_to_delete);
        }
        elements.insert({new_w, new_l});
    }
    long long int GetBestLength(const long long int w) const {
        auto it = elements.lower_bound({w, std::numeric_limits<long long int>::max()});
        if (it == elements.begin()) {
            return 0;
        } else {
            --it;
            return it->l;
        }
    }
    long long int GetMaxPossibleLength() const {
        if (elements.size()) {
            return elements.rbegin()->l;
        } else {
            return 0;
        }
    }
    std::set<Element> elements;
};

int main() {
    std::ios::sync_with_stdio(false);
    long long int n;
    long long int m;
    std::cin >> n >> m;
    std::vector<BiSet> bisets(n);
    for (long long int i = 0; i < m; ++i) {
        long long int first_vertex, second_vertex, weight;
        std::cin >> first_vertex >> second_vertex >> weight;
        --first_vertex;
        --second_vertex;
        long long max_prev_length = bisets[first_vertex].GetBestLength(weight);
        bisets[second_vertex].Insert(weight, max_prev_length + 1);
    }
    long long int max_length = 0;
    for (long long int i = 0; i < n; ++i) {
        max_length = std::max(max_length, bisets[i].GetMaxPossibleLength());
    }
    std::cout << max_length << std::endl;
    return 0;
}
