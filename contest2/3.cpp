#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

void BreadthFastSearch(
    std::vector<std::unordered_set<long long int> >& tree,
    std::unordered_set<long long int>& black
) {
    std::unordered_set<long long int> grey;
    while (1) {
        for (auto it = black.begin(); it != black.end(); ++it) {
            for (auto it2 = tree[*it].begin(); it2 != tree[*it].end(); ++it2) {
                if (black.count(*it2) == 0) {
                    grey.insert(*it2);
                }
            }
        }
        for (auto it = grey.begin(); it != grey.end(); ++it) {
            black.insert(*it);
        }
        if (grey.size() == 0) {
            break;
        }
        grey = std::unordered_set<long long int>();
    }
}

//void visit(
//        long long int n,
//        std::unordered_set<long long int>& not_marked,
//        std::unordered_set<long long int>& temporary_marked,
//        std::vector<long long int>& L,
//        std::unordered_map<long long int, std::unordered_set<long long int> >& tree,
//        bool& is_possible
//) {
//    if (!is_possible) {
//        return;
//    }
//    if (temporary_marked.count(n) > 0) {
//        is_possible = false;
//        return;
//    }
//    if (not_marked.count(n) > 0) {
//        temporary_marked.insert(n);
//        if (tree.count(n) > 0) {
//            for (auto it = tree[n].begin(); it != tree[n].end(); ++it) {
//                visit(*it, not_marked, temporary_marked, L, tree, is_possible);
//            }
//        }
//        not_marked.erase(n);
//        temporary_marked.erase(n);
//        L.push_back(n);
//    }
//}


void print_tree(
        const long long int n,
        std::unordered_map<long long int, std::unordered_set<long long int> > tree,
        std::unordered_map<long long int, std::unordered_set<long long int> > reverse_tree
) {
    std::cout << "tree\n";

    for (size_t i = 0; i < n; ++i) {
        std::cout << i + 1 << std::endl;
        for (auto it = tree[i].begin(); it != tree[i].end(); ++it) {
            std::cout << "\t" << *it + 1 << std::endl;
        }
    }
    std::cout << "reverse tree\n";
    for (size_t i = 0; i < n; ++i) {
        std::cout << i + 1 << std::endl;
        for (auto it = reverse_tree[i].begin(); it != reverse_tree[i].end(); ++it) {
            std::cout << "\t" << *it + 1 << std::endl;
        }
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

    std::vector<std::unordered_set<long long int> > reverse_tree(n);
    std::vector<std::unordered_set<long long int> > tree(n);

    for (size_t i = 0; i < n; ++i) {
        long long int count_of_depends;
        std::cin >> count_of_depends;
        for (size_t j = 0; j < count_of_depends; ++j) {
            long long int parent;
            std::cin >> parent;
            parent -= 1;
            tree[i].insert(parent);
            reverse_tree[parent].insert(i);
        }
    }

    BreadthFastSearch(tree, needed_courses);
//    print_tree(n, tree, reverse_tree);

//    for (size_t i = 0; i < n; ++i) {
//        if (needed_courses.count(i) == 0) {
//            std::unordered_set<long long int> parents(tree[i]);
//            std::unordered_set<long long int> children(reverse_tree[i]);
//            for (auto it = parents.begin(); it != parents.end(); ++it) {
//                reverse_tree[*it].erase(i);
//                tree[i].erase(*it);
//            }
//            for (auto it = children.begin(); it != children.end(); ++it) {
//                reverse_tree[i].erase(*it);
//                tree[*it].erase(i);
//            }
//        }
//    }
//
//    std::vector<long long int> L;
//    std::unordered_set<long long int> temporary_marked;
//    std::unordered_set<long long int> not_marked = all_courses;
//    bool is_possible = true;

//    while (not_marked.size() > 0 && is_possible) {
//        long long int n = *(not_marked.begin());
//        visit(n, not_marked, temporary_marked, L, reverse_tree, is_possible);
//    }

//    print_tree(n, tree, reverse_tree);

    std::unordered_set<long long int> S;
    std::vector<long long int> L;

    for (size_t i = 0; i < n; ++i) {
        if (tree[i].size() == 0 && needed_courses.count(i) > 0) {
            S.insert(i);
        }
    }

    while (S.size() > 0) {
        long long int some_course = *(S.begin());
        S.erase(some_course);
        if (needed_courses.count(some_course)) {
            L.push_back(some_course);
        }
        std::unordered_set<long long int> children = reverse_tree[some_course];
        for (auto it = children.begin(); it != children.end(); ++it) {
            reverse_tree[some_course].erase(*it);
            tree[*it].erase(some_course);

            if (tree[*it].size() == 0) {
                S.insert(*it);
            }
        }
    }

    bool does_tree_have_edges = false;
    for (size_t i = 0; i < n; ++i) {
        if (tree[i].size() > 0) {
            does_tree_have_edges = true;
        }
    }

    if (does_tree_have_edges) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << L.size() << std::endl;

        for (size_t i = 0; i < L.size(); ++i) {
            std::cout << L[i] + 1;
            if (i + 1 < L.size()) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

