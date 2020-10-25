#include <cstdlib>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>

struct Edge {
    int a;
    int b;
    int w;
};

struct Graph {
    int n;
    std::vector<Edge> edges;
};

Graph GenerateRandomGraph() {
    Graph g;
    g.n = rand() % 10 + 4;
    int m = rand() % std::min(1000 - g.n, g.n * (g.n - 3) / 2) + g.n;
    for (int i = 0; i < m; ++i) {
        g.edges.push_back({rand() % g.n, rand() % g.n, rand() % 10 + 1});
    }
    return g;
}

bool AreEdgesDistinct(const Graph& g) {
    std::unordered_set<int> used_edges;
    for (const Edge& edge : g.edges) {
        if (edge.a == edge.b) {
            return false;
        }
        if (used_edges.count(edge.a * g.n + edge.b) > 0)   {
            return false;
        }
        used_edges.insert(edge.a * g.n + edge.b);
        used_edges.insert(edge.b * g.n + edge.a);
    }
    return true;
}

void FillVisited(int node, const Graph& g, std::vector<bool>& is_visited) {
    if (is_visited[node]) {
        return;
    }
    is_visited[node] = true;
    for (const Edge& edge : g.edges) {
        if (edge.a == node) {
            FillVisited(edge.b, g, is_visited);
        }
    }
}

bool IsOneComponent(const Graph& g) {
    std::vector<bool> is_visited(g.n, false);
    FillVisited(0, g, is_visited);
    for (bool visited : is_visited) {
        if (!visited) {
            return false;
        }
    }
    return true;
}

bool ValidateGraph(const Graph& g) {
    return AreEdgesDistinct(g) && IsOneComponent(g);
}

void Test() {
    Graph g;
    do {
        g = GenerateRandomGraph();
    } while (!ValidateGraph(g));
    std::ofstream out("input");
    int k = rand() % 3 + 1;
    out << g.n << " " << g.edges.size() << " " << k << std::endl;
    for (const Edge& edge : g.edges) {
        out << edge.a + 1 << " " << edge.b + 1 << " " << edge.w << std::endl;
    }
    for (int i = 0; i < k; ++i) {
        out << rand() % g.n + 1 << " " << rand() % g.n + 1 << std::endl;
    }
    out.close();
    if (system("./7.o < input > 7-output")) {
        throw std::runtime_error("7.o failed");
    }
    if (system("./7-correct.o < input > 7-correct-output")) {
        throw std::runtime_error("7-correct.o failed");
    }
    if (system("diff 7-correct-output 7-output")) {
        throw std::runtime_error("there's diff");
    }
    std::cout << "OK\n";
}

int main() {
    for (int i = 0; i < 100; ++i) {
        Test();
    }
    return 0;
}
