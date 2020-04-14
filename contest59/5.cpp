#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

class LazySegmentTree {
public:
    LazySegmentTree(int size): mins(CalcTreeSize(size), 0), maxs(CalcTreeSize(size), 0), addons(CalcTreeSize(size), 0), size(size) {}

    int GetTotalMin() const {
        return mins[0];
    }

    int GetTotalMax() const {
        return maxs[0];
    }

    void AddOnSegment(int left, int right, int toadd) {
        if (left >= right) {
            return;
        }
        AddOnSegment(0, 0, size, left, right, toadd);
    }
private:
    static int CalcTreeSize(int size) {
        int lower = 0;
        int node = 0;
        while (size - lower > 1) {
            lower = (size + lower) / 2;
            node = node * 2 + 2;
        }
        return node + 10;
    }

    void AddOnSegment(int node, int node_left, int node_right, int left, int right, int toadd) {
        if (left >= right) {
            return;
        }
        if (node_left >= node_right) {
            return;
        }
        if (node_left == left && node_right == right) {
            addons[node] += toadd;
            mins[node] += toadd;
            maxs[node] += toadd;
        } else {
            int node_mid = (node_left + node_right) / 2;
            AddOnSegment(node * 2 + 1, node_left, node_mid, left, std::min(right, node_mid), toadd);
            AddOnSegment(node * 2 + 2, node_mid, node_right, std::max(left, node_mid), right, toadd);
            mins[node] = std::min(mins[node * 2 + 1], mins[node * 2 + 2]) + addons[node];
            maxs[node] = std::max(maxs[node * 2 + 1], maxs[node * 2 + 2]) + addons[node];
        }
    }

    std::vector<int> mins;
    std::vector<int> maxs;
    std::vector<int> addons;
    int size;
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    LazySegmentTree lazy_segment_tree(n + 1);
    int bracket_balance = 0;
    std::string commands;
    std::cin >> commands;
    std::string input(n + 1, ' ');
    int current_index = 0;
    for (int i = 0; i < n; ++i) {
        char ch = commands[i];
        if (ch == 'R') {
            ++current_index;
        } else if (ch == 'L') {
            if (current_index > 0) {
                --current_index;
            }
        } else {
            char prev_symbol = input[current_index];
            int toadd = 0;
            if (prev_symbol == '(') {
                --toadd;
            } else if (prev_symbol == ')') {
                ++toadd;
            }
            if (ch == '(') {
                ++toadd;
            } else if (ch == ')') {
                --toadd;
            }
            if (toadd != 0) {
                lazy_segment_tree.AddOnSegment(current_index, n + 1, toadd);
                bracket_balance += toadd;
            }
            input[current_index] = ch;
        }
        if (bracket_balance == 0 && lazy_segment_tree.GetTotalMin() == 0) {
            std::cout << lazy_segment_tree.GetTotalMax();
        } else {
            std::cout << -1;
        }
        if (i + 1 < n) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}

