#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>

template<typename T>
long long int GetInversionsCountRecursive(std::vector<T>& data, std::vector<T>& another_data, const size_t start_index,const size_t finish_index) {
    if (start_index == finish_index) {
        return 0;
    } else if (start_index + 1 == finish_index) {
        return 0;
    } else {
        size_t middle_index = (finish_index + start_index) / 2;
        long long int inversions = 0;
        inversions += GetInversionsCountRecursive(data, another_data, start_index, middle_index);
        inversions += GetInversionsCountRecursive(data, another_data, middle_index, finish_index);
        size_t first_index = start_index;
        size_t second_index = middle_index;
        size_t target_index = start_index;
        while (first_index < middle_index && second_index < finish_index) {
            if (data[first_index] < data[second_index]) {
                another_data[target_index++] = data[first_index++];
            } else {
                inversions += middle_index - first_index;
                another_data[target_index++] = data[second_index++];
            }
        }
        while (first_index < middle_index) {
            another_data[target_index++] = data[first_index++];
        }
        while (second_index < finish_index) {
            another_data[target_index++] = data[second_index++];
        }
        for (size_t i = start_index; i < finish_index; ++i) {
            data[i] = another_data[i];
        }
        return inversions;
    }
}

template<typename T>
long long int GetInversionsCount(std::vector<T>& data) {
    std::vector<T> another_data(data.size());
    return GetInversionsCountRecursive(data, another_data, 0, data.size());
}

long long int GetIntersectionsCount(
    const std::vector<std::pair<long long int, long long int>>& points,
    const long long int h
) {
    std::vector<long long int> upper_cells;
    for (auto& point: points) {
        long long int x = point.first;
        long long int y = point.second;
        upper_cells.push_back(x - y);
    }
    std::sort(upper_cells.begin(), upper_cells.end());
    long long int intersections_count = 0;
    for (auto& point: points) {
        long long int x = point.first;
        long long int y = point.second;
        long long int upper_inclusive = x + y;
        long long int lower_inclusive = upper_inclusive - 2ll * h + 1ll;
        intersections_count += std::upper_bound(upper_cells.begin(), upper_cells.end(), upper_inclusive)
            - std::lower_bound(upper_cells.begin(), upper_cells.end(), lower_inclusive);
    }
    return intersections_count;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    long long int h;
    std::cin >> n;
    std::cin >> h;
    std::vector<std::pair<long long int, long long int>> black_points;
    std::vector<std::pair<long long int, long long int>> white_points;
    for (int i = 0; i < n; ++i) {
        long long int x,y;
        std::cin >> x >> y;
        if ((x + y) % 2 == 0) {
            white_points.push_back({x, y});
        } else {
            black_points.push_back({x, y});
        }
    }
    long long int result = 2ll * h * static_cast<long long int>(n) - GetIntersectionsCount(black_points, h) - GetIntersectionsCount(white_points, h)
        - static_cast<long long int>(n);
    std::cout << result << std::endl;
    return 0;
}
