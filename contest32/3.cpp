#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
#include <iostream>
#include <limits>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Mainly for demonstration purposes, i.e. works but is overly simple
        // In the real world, use sth. like boost.hash_combine
        return h1 ^ h2;
    }
};

class Tree {
private:
    struct Node {
        std::string project_name;
        int version;
        std::vector<size_t> deps;
    };
    struct BFSQueueElement {
        size_t index;
        size_t distance;
    };
public:
    Tree()
        : nodes(1000)
        , project_index()
        , max_used_index(0)
    {}

    size_t AddNode(const std::string& name, const int version) {
        std::pair<std::string, int> name_and_versaion = std::make_pair(name, version);
        if (project_index.count(name_and_versaion) == 0) {
            project_index[name_and_versaion] = max_used_index;
            nodes[max_used_index] = {name, version, {}};
            ++max_used_index;
        }
        return project_index[name_and_versaion];
    }

    void AddEdge(const std::string& first_name, const int first_version, const std::string& second_name, const int second_version) {
        auto first_node_index = AddNode(first_name, first_version);
        auto second_node_index = AddNode(second_name, second_version);
        nodes[first_node_index].deps.push_back(second_node_index);
    }

    std::vector<std::pair<std::string, int>> GetDeps() {
        std::list<BFSQueueElement> bfs_queue;
        bfs_queue.push_back({0, 0});
        size_t max_distance = std::numeric_limits<size_t>::max();
        std::unordered_map<std::string, int> project_max_version;
        std::vector<std::pair<std::string, int>> result;
        std::vector<bool> is_visited(max_used_index + 1, false);
        is_visited[0] = 0;
        while (bfs_queue.size() > 0) {
            auto bfs_first_element = bfs_queue.front();
            if (bfs_first_element.distance != max_distance) {
                max_distance = bfs_first_element.distance;
                std::list<BFSQueueElement> new_bfs_queue;
                for (auto bfs_element: bfs_queue) {
                    std::string project_name = nodes[bfs_element.index].project_name;
                    int version = nodes[bfs_element.index].version;
                    if (project_max_version.count(project_name) == 0 || project_max_version[project_name] < version) {
                        project_max_version[project_name] = version;
                    }
                }
                for (auto bfs_element: bfs_queue) {
                    std::string project_name = nodes[bfs_element.index].project_name;
                    int version = nodes[bfs_element.index].version;
                    if (project_max_version[project_name] == version) {
                        new_bfs_queue.push_back(bfs_element);
                    }
                }
                bfs_queue = std::move(new_bfs_queue);
            }
            if (bfs_queue.size() == 0) {
                break;
            }
            bfs_first_element = bfs_queue.front();
            bfs_queue.pop_front();
            auto& node = nodes[bfs_first_element.index];
            if (bfs_first_element.index > 0) {
                result.push_back(std::make_pair(node.project_name, node.version));
            }
            for (auto& dep_index: nodes[bfs_first_element.index].deps) {
                std::string project_name = nodes[dep_index].project_name;
                if (project_max_version.count(project_name) == 0 && !is_visited[dep_index]) {
                    is_visited[dep_index] = true;
                    bfs_queue.push_back({dep_index, max_distance + 1});
                }
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

private:
    std::vector<Node> nodes;
    std::unordered_map<std::pair<std::string, int>, size_t, pair_hash> project_index;
    size_t max_used_index = 0;
};

int main() {
    int n;
    std::cin >> n;
    Tree tree;
    for (int i = 0 ; i < n; ++i) {
        std::string project_name;
        int version;
        std::cin >> project_name >> version;
        tree.AddNode(project_name, version);
        int k;
        std::cin >> k;
        for (int j = 0; j < k; ++j) {
            std::string dep_project_name;
            int dep_version;
            std::cin >> dep_project_name >> dep_version;
            tree.AddEdge(project_name, version, dep_project_name, dep_version);
        }
    }
    auto deps = tree.GetDeps();
    std::cout << deps.size() << std::endl;
    for (size_t i = 0; i < deps.size(); ++i) {
        auto pair = deps[i];
        std::cout << pair.first << " " << pair.second << std::endl;
    }
    return 0;
}
