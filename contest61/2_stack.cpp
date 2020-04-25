#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> GetPreviousDistance(const std::vector<long long int>& heights) {
    std::vector<int> prev_distance(heights.size());
    std::vector<int> increasing_height_indices;
    for (int i = 0; i < static_cast<int>(heights.size()); ++i) {
        while (increasing_height_indices.size() > 0 && heights[increasing_height_indices.back()]>= heights[i]) {
            increasing_height_indices.pop_back();
        }
        prev_distance[i] = i - (increasing_height_indices.size() > 0 ? increasing_height_indices.back() : -1);
        increasing_height_indices.push_back(i);
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
