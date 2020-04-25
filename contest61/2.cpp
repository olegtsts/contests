#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

class SegmentTree {
public:
    SegmentTree(int size): maxs(CalcTreeSize(size), -1), size(size) {}

    long long int GetMaxOnSegment(int left, int right) {
        return GetMaxOnSegment(0, 0, size, left, right);
    }

    void UpdateIndex(int index, long long int new_value) {
        UpdateIndexOnSegment(0, 0, size, index, new_value);
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

    long long int GetMaxOnSegment(int node, int node_left, int node_right, int left, int right) {
        assert(right <= node_right);
        if (left >= right) {
            return -1;
        }
        if (node_left >= node_right) {
            return -1;
        }
        if (node_left == left && node_right == right) {
            return maxs[node];
        } else {
            int node_mid = (node_left + node_right) / 2;
            return std::max(
                GetMaxOnSegment(node * 2 + 1, node_left, node_mid, left, std::min(right, node_mid)),
                GetMaxOnSegment(node * 2 + 2, node_mid, node_right, std::max(left, node_mid), right));
        }
    }

    void UpdateIndexOnSegment(int node, int node_left, int node_right, int index, long long int new_value) {
        if (index >= node_right) {
            return;
        }
        if (index < node_left) {
            return;
        }
        if (node_left >= node_right) {
            return;
        }
        if (node_left == index && node_right == index + 1) {
            maxs[node] = new_value;
        } else {
            int node_mid = (node_left + node_right) / 2;
            UpdateIndexOnSegment(node * 2 + 1, node_left, node_mid, index, new_value);
            UpdateIndexOnSegment(node * 2 + 2, node_mid, node_right, index, new_value);
            maxs[node] = std::max(maxs[node * 2 + 1], maxs[node * 2 + 2]);
        }
    }

    std::vector<long long int> maxs;
    int size;
};

std::vector<int> GetPreviousDistance(const std::vector<long long int>& heights) {
    std::vector<int> prev_distance(heights.size());
    SegmentTree heights_indices_tree(1000001);
    for (int i = 0; i < static_cast<int>(heights.size()); ++i) {
        prev_distance[i] = i - heights_indices_tree.GetMaxOnSegment(0, heights[i]);
        heights_indices_tree.UpdateIndex(heights[i], i);
    }
    return prev_distance;
}


int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<long long int> heights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> heights[i];
    }
    std::vector<int> prev_distance = GetPreviousDistance(heights);
    std::reverse(heights.begin(), heights.end());
    std::vector<int> post_distance = GetPreviousDistance(heights);
    std::reverse(post_distance.begin(), post_distance.end());
    std::reverse(heights.begin(), heights.end());
    long long int max_area = 0;
    for (int i = 0; i < n; ++i) {
        max_area = std::max(max_area, (prev_distance[i] + post_distance[i] - 1) * heights[i]);
    }
    std::cout << max_area << std::endl;
    return 0;
}
