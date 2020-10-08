#include <vector>
#include <algorithm>
#include <iostream>

class LazySumSegmentTree {
public:
    LazySumSegmentTree(int size) : sums(CalcTreeSize(size), 0), addons(CalcTreeSize(size), 0), size(size) {
    }

    void AddOnSegment(int left, int right, int64_t toadd) {
        AddOnSegment(0, 0, size, left, right, toadd);
    }

    int64_t GetOnSegment(int left, int right) const {
        return GetOnSegment(0, 0, size, left, right, 0);
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

    void AddOnSegment(int node, int node_left, int node_right, int left, int right, int64_t toadd) {
        if (left >= right) {
            return;
        }
        if (node_left >= node_right) {
            return;
        }
        if (node_left == left && node_right == right) {
            addons[node] += toadd;
            sums[node] += toadd * (node_right - node_left);
        } else {
            int node_mid = (node_left + node_right) / 2;
            AddOnSegment(node * 2 + 1, node_left, node_mid, left, std::min(right, node_mid), toadd);
            AddOnSegment(node * 2 + 2, node_mid, node_right, std::max(left, node_mid), right, toadd);
            sums[node] = sums[node * 2 + 1] + sums[node * 2 + 2] + addons[node] * (node_right - node_left);
        }
    }

    int64_t GetOnSegment(int node, int node_left, int node_right, int left, int right, int64_t addon) const {
        if (left >= right) {
            return 0;
        }
        if (node_left >= node_right) {
            return 0;
        }
        if (node_left == left && node_right == right) {
            return sums[node] + addon * (node_right - node_left);
        } else {
            int node_mid = (node_left + node_right) / 2;
            return GetOnSegment(node * 2 + 1, node_left, node_mid, left, std::min(right, node_mid), addon + addons[node]) +
                GetOnSegment(node * 2 + 2, node_mid, node_right, std::max(left, node_mid), right, addon + addons[node]);
        }
    }
private:
    std::vector<int64_t> sums;
    std::vector<int64_t> addons;
    int size;
};

class IncreasesSumComputer {
public:
    IncreasesSumComputer(int size): segment_tree(size), increases_sum(0), size(size) {}

    void AddOnSegment(int left, int right, int64_t addon) {
        ApplyBorderChanges(-1, left, right);
        segment_tree.AddOnSegment(left, right, addon);
        ApplyBorderChanges(1, left, right);
    }

    int64_t GetIncreasesSum() const {
        int64_t result = segment_tree.GetOnSegment(0, 1) + increases_sum;
        if (result % 2 == 0) {
            return result / 2;
        } else {
            return (result - 1) / 2 + 1;
        }
    }
private:

    int64_t GetIncrease(int64_t first, int64_t second) const {
        return std::max(second - first, int64_t(0));
    }

    void ApplyBorderChanges(int64_t coef, int left, int right) {
        if (left > 0) {
            increases_sum += coef * GetIncrease(segment_tree.GetOnSegment(left - 1, left), segment_tree.GetOnSegment(left, left + 1));
        }
        if (right < size) {
            increases_sum += coef * GetIncrease(segment_tree.GetOnSegment(right - 1, right), segment_tree.GetOnSegment(right, right + 1));
        }
    }

    LazySumSegmentTree segment_tree;
    int64_t increases_sum;
    int size;
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    IncreasesSumComputer computer(n);
    for (int i = 0; i < n; ++i) {
        int64_t number;
        std::cin >> number;
        computer.AddOnSegment(i, i + 1, number);
    }
    std::cout << computer.GetIncreasesSum() << std::endl;
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int left;
        int right;
        int64_t x;
        std::cin >> left >> right >> x;
        --left;
        computer.AddOnSegment(left, right, x);
        std::cout << computer.GetIncreasesSum() << std::endl;
    }
    return 0;
}
