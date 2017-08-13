#include <iostream>
#include <unordered_set>
#include <vector>
#include <iomanip>
#include <string>

template <typename Container>
void Output(const std::string& name, const Container& container) {
    std::cout << name << " = ";
    for (auto& el: container) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

void Extend(
    std::unordered_set<int>& compsub,
    std::unordered_set<int>& candidates,
    std::unordered_set<int>& not_candidates,
    std::vector<std::vector<int>>& graph,
    int& max_clique
) {
    while(true) {
        if (candidates.size() == 0) {
            break;
        }
        bool continue_condition = true;
        for(auto& vertex: not_candidates) {
            bool connected_with_all = true;
            for (auto& cand: candidates) {
                if (!graph[vertex][cand]) {
                    connected_with_all = false;
                    break;
                }
            }
            if (connected_with_all) {
                continue_condition = false;
                break;
            }
        }
        if (!continue_condition) {
            break;
        }
        int v = *(candidates.begin());
        compsub.insert(v);
        std::unordered_set<int> new_candidates;
        std::unordered_set<int> new_not_candidates;
        for (auto& node: candidates) {
            if (graph[v][node]) {
                new_candidates.insert(node);
            }
        }
        for (auto& node: not_candidates) {
            if (graph[v][node]) {
                new_not_candidates.insert(node);
            }
        }
        if (new_candidates.size() == 0 && new_not_candidates.size() == 0) {
            if (static_cast<size_t>(max_clique) < compsub.size()) {
                max_clique = compsub.size();
            }
        } else {
            Extend(compsub, new_candidates, new_not_candidates, graph, max_clique);
        }
        compsub.erase(v);
        candidates.erase(v);
        not_candidates.insert(v);
    }
}

int GetCliqueSize(const int n, std::vector<std::vector<int>>& graph) {
    std::unordered_set<int> compsub;
    std::unordered_set<int> candidates;
    std::unordered_set<int> not_candidates;
    for (int i = 0; i < n; ++i) {
        candidates.insert(i);
    }
    int max_clique = 0;
    Extend(compsub, candidates, not_candidates, graph, max_clique);
    return max_clique;
}

int main() {
    int n;
    long double k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int is_edge;
            std::cin >> is_edge;
            graph[i].push_back(is_edge);
        }
    }
    const int clique_size = GetCliqueSize(n, graph);
    std::cout << std::setprecision(10) << k * k * static_cast<long double>(clique_size - 1)
        / 2 / static_cast<long double>(clique_size) << std::endl;
    return 0;
}
//http://codeforces.com/contest/839/problem/E
