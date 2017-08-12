#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;


struct Node {
    int id;
    double probability;
    double path_length;

    Node(int id, double probability, double path_length)
       : id(id), probability(probability), path_length(path_length) {}
};


int main() {
    int n, x, y;
    stack<Node> s;
    bool edge;
    double neighbors;
    double result = 0.0;

    cin >> n;
    vector<bool> used(n);
    vector<vector<int> > adj(n, vector<int>());

    for (int i = 0; i < n - 1; ++i) {
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    s.push(Node{0, 1.0, 0.0});
    used[0] = true;

    while (!s.empty()) {
        Node v = s.top();
        s.pop();
        edge = true;
        neighbors = 0.0;

        for (size_t i = 0; i < adj[v.id].size(); ++i) {
            if (!used[adj[v.id][i]]) {
                ++neighbors;
            }
        }

        for (size_t i = 0; i < adj[v.id].size(); ++i) {
            if (!used[adj[v.id][i]]) {
                edge = false;
                s.push(Node{adj[v.id][i], 1.0/neighbors * v.probability, v.path_length + 1.0});
                used[adj[v.id][i]] = 1;
            }
        }

        if (edge) {
            result += v.probability * v.path_length;
        }
    }

    cout << std::setprecision(10) << result << endl;

    return 0;
}
