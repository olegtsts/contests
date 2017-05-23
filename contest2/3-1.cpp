#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>


void visit(
    long long int node,
    std::vector<std::unordered_set<long long int> >& tree,
    std::vector<int>& states,
    std::vector<long long int>& result_list,
    bool& cycle_found
) {
    if (cycle_found) {
        return;
    } else if (states[node] == 0) {
        states[node] = 1;
        for (auto it = tree[node].begin(); it != tree[node].end(); ++it) {
            visit(*it, tree, states, result_list, cycle_found);
        }
        states[node] = 2;
        result_list.push_back(node);
    } else if (states[node] == 1) {
        cycle_found = true;
    } else if (states[node] == 2) {
        // Do nothing
    }
}

int main() {
    std::unordered_set<long long int> needed_courses;

    long long int n,k;

    std::cin >> n >> k;
    for (size_t i = 0; i < k; ++i) {
        long long int main_course;
        std::cin >> main_course;
        needed_courses.insert(main_course - 1);
    }

    std::vector<std::unordered_set<long long int> > tree(n);

    for (size_t i = 0; i < n; ++i) {
        long long int count_of_depends;
        std::cin >> count_of_depends;
        for (size_t j = 0; j < count_of_depends; ++j) {
            long long int parent;
            std::cin >> parent;
            parent -= 1;
            tree[i].insert(parent);
        }
    }

    std::vector<long long int> result_list;
    std::vector<int> states(n);
    bool cycle_found = false;

    for (auto it = needed_courses.begin(); it != needed_courses.end(); ++it) {
        visit(*it, tree, states, result_list, cycle_found);
        if (cycle_found) {
            break;
        }
    }

    if (cycle_found) {
        std::cout << "-1" << std::endl;
    } else {
        std::cout << result_list.size() << std::endl;
        for (auto i = 0; i != result_list.size(); ++i) {
            std::cout << result_list[i] + 1;
            if (i + 1 < result_list.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
