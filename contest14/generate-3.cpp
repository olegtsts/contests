#include <cstdlib>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <tuple>
#include <iostream>

auto generate_random_graph() {
    int n = rand() % 5 + 2;
    std::vector<int> sequence(n - 2);
    for (int i = 0; i + 2 < n; ++i) {
        sequence[i] = rand() % (n - 1);
    }
    std::vector<std::pair<int, int>> graph;
    std::vector<int> degree(n, 1);
    for (auto& value: sequence) {
        ++degree[value];
    }
    for (auto& i: sequence) {
        for (int j = 0; j < n; ++j) {
            if (degree[j] == 1) {
                graph.push_back(std::make_pair(i, j));
                --degree[i];
                --degree[j];
                break;
            }
        }
    }

    int u(0);
    int v(0);
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) {
            if (u == 0) {
                u = i;
            } else {
                v = i;
            }
        }
    }
    graph.push_back(std::make_pair(u, v));
    return std::make_tuple(n, graph);
}

void write_to_file(const int n, const std::vector<std::pair<int, int>>& graph, const std::string& filename) {
    std::ofstream out(filename);

    out << n << std::endl;
    for (auto& cur_pair: graph) {
        out << cur_pair.first + 1 << " " << cur_pair.second + 1 << std::endl;
    }
}

int main() {
    std::vector<std::pair<int, int>> graph;
    int n;
    for (int i = 0; i < 1000; ++i) {
        std::tie(n, graph) = generate_random_graph();
        write_to_file(n, graph, "file");
        system("./3.out < file > 3.result");
        system("./3-other.out < file > 3-other.result");
        if (system("diff 3.result 3-other.result")) {
            throw 123;
        } else {
            std::cout << "Ok test\n";
        }
    }

    return 0;
}
