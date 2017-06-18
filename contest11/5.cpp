#include <iostream>
#include <vector>

long long int NO_COST = 1000000001;

void dfs(
    const int current,
    std::vector<long long int>& costs_without_root,
    std::vector<long long int>& costs_with_root,
    std::vector<std::vector<int> >& children,
    std::vector<long long int>& c,
    std::vector<long long int>& d,
    const int n
) {
    std::vector<long long int> current_costs_without_root{0, c[current]};
    std::vector<long long int> current_costs_with_root{NO_COST, c[current] - d[current]};
    for (auto& child: children[current]) {
        std::vector<long long int> child_costs_without_root;
        std::vector<long long int> child_costs_with_root;
        dfs(child, child_costs_without_root, child_costs_with_root, children, c, d, n);
        std::vector<long long int> new_costs_without_root(current_costs_without_root.size()
                + child_costs_without_root.size() - 1, NO_COST);
        for (size_t i = 0; i < child_costs_without_root.size(); ++i) {
            for (size_t j = 0; j < current_costs_without_root.size(); ++j) {
                new_costs_without_root[i + j] = std::min(
                        new_costs_without_root[i + j],
                        current_costs_without_root[j] + child_costs_without_root[i]);
            }
        }
        std::vector<long long int> new_costs_with_root(
                current_costs_with_root.size() + std::max(child_costs_without_root.size(),
                    child_costs_with_root.size()) - 1, NO_COST);
        for (size_t i = 1; i < child_costs_with_root.size(); ++i) {
            for (size_t j = 1; j < current_costs_with_root.size(); ++j) {
                new_costs_with_root[i + j] = std::min(
                        new_costs_with_root[i + j],
                        current_costs_with_root[j] + child_costs_with_root[i]);
            }
        }
        for (size_t i = 0; i < child_costs_without_root.size(); ++i) {
            for (size_t j = 1; j < current_costs_with_root.size(); ++j) {
                new_costs_with_root[i + j] = std::min(
                        new_costs_with_root[i + j],
                        current_costs_with_root[j] + child_costs_without_root[i]);
            }
        }
        current_costs_without_root = std::move(new_costs_without_root);
        current_costs_with_root = std::move(new_costs_with_root);
    }
    costs_with_root = std::move(current_costs_with_root);
    costs_without_root = std::move(current_costs_without_root);
}

int main() {
    int n;
    long long int b;
    std::cin >> n >> b;
    std::vector<long long int> c(n);
    std::vector<long long int> d(n);
    std::vector<std::vector<int> > children(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> c[i] >> d[i];
        if (i >= 1) {
            int depend_on;
            std::cin >> depend_on;
            --depend_on;
            children[depend_on].push_back(i);
        }
    }
    std::vector<long long int> costs_without_root;
    std::vector<long long int> costs_with_root;
    dfs(0, costs_without_root, costs_with_root, children, c, d, n);
    int max_possible_goods = 0;
    for (size_t i = 0; i < costs_with_root.size(); ++i) {
        if (costs_with_root[i] <= b) {
            if (max_possible_goods < i) {
                max_possible_goods = i;
            }
        }
    }
    for (size_t i = 0; i < costs_without_root.size(); ++i) {
        if (costs_without_root[i] <= b) {
            if (max_possible_goods < i) {
                max_possible_goods = i;
            }
        }
    }
    std::cout << max_possible_goods << std::endl;
    return 0;
}


