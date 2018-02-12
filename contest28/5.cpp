#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <tuple>

struct VertexInfo {
    int subtree_size = 0;
    int max_sec_root_last = 0;
    int max_sec_without_deletion = 0;

    bool operator<(const VertexInfo& other) const {
        int difference = subtree_size - max_sec_without_deletion;
        int other_difference = other.subtree_size - other.max_sec_without_deletion;
        return difference < other_difference || (
            difference == other_difference &&
            std::make_tuple(subtree_size, max_sec_root_last, max_sec_without_deletion) <
            std::make_tuple(other.subtree_size, other.max_sec_root_last, other.max_sec_without_deletion));
    }
};

VertexInfo GetVertexInfo(
    const std::vector<std::vector<int>>& children,
    int vertex,
    int k
) {
    VertexInfo current_info;
    current_info.subtree_size = 1;
    std::vector<VertexInfo> child_infos;
    for (auto& child: children[vertex]) {
        child_infos.push_back(GetVertexInfo(children, child, k));
        current_info.subtree_size += child_infos.back().subtree_size;
        current_info.max_sec_root_last += child_infos.back().max_sec_without_deletion;
        current_info.max_sec_without_deletion += child_infos.back().max_sec_without_deletion;
    }
    if (static_cast<int>(child_infos.size()) < k - 1) {
        for (int i = 0; i < static_cast<int>(child_infos.size()); ++i) {
            current_info.max_sec_without_deletion += child_infos[i].subtree_size - child_infos[i].max_sec_without_deletion;
            current_info.max_sec_root_last += child_infos[i].subtree_size - child_infos[i].max_sec_without_deletion;
        }
        return current_info;
    } else {
        std::sort(child_infos.rbegin(), child_infos.rend());
        int max_profit = std::numeric_limits<int>::min();
        for (int i = 0; i < k - 2; ++i) {
            current_info.max_sec_without_deletion += child_infos[i].subtree_size - child_infos[i].max_sec_without_deletion;
        }
        for (int i = 0; i < k - 1; ++i) {
            VertexInfo& child_info = child_infos[i];
            current_info.max_sec_root_last += child_info.subtree_size - child_info.max_sec_without_deletion;
            int profit = child_info.max_sec_root_last + 1 - child_info.max_sec_without_deletion - (child_info.subtree_size - child_info.max_sec_without_deletion);
            if (max_profit < profit) {
                max_profit = profit;
            }
        }
        for (int i = k - 1; i < static_cast<int>(child_infos.size()); ++i) {
            VertexInfo& child_info = child_infos[i];
            int profit = child_info.max_sec_root_last + 1 - child_info.max_sec_without_deletion - (child_infos[k - 2].subtree_size - child_infos[k - 2].max_sec_without_deletion);
            if (max_profit < profit) {
                max_profit = profit;
            }
        }
        current_info.max_sec_root_last += max_profit;
        return current_info;
    }
}

void Solve() {
    int n;
    std::cin >> n;
    int k;
    std::cin >> k;
    std::vector<std::vector<int>> children(n);
    for (int i = 0; i + 1 < n; ++i) {
        int parent;
        std::cin >> parent;
        --parent;
        children[parent].push_back(i);
    }
    std::cout << GetVertexInfo(children, n - 1, k).max_sec_root_last << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        Solve();
    }
    return 0;
}
