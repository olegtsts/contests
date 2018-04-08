#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <cstdio>

struct Segment {
    long double min_value;
    long double max_value;
    bool is_empty;
    bool is_full;
};

Segment DFS(
    const std::vector<std::vector<int>>& neighbours,
    const std::vector<bool>& is_star,
    const std::vector<long double>& x,
    long double result_distance,
    std::vector<bool>& is_visited,
    const int current_node
) {
    is_visited[current_node] = true;
    long double max_of_min_values = -std::numeric_limits<long double>::max();
    long double min_of_max_values = std::numeric_limits<long double>::max();
    bool is_restricted = false;
    for (auto& neighbour: neighbours[current_node]) {
        if (!is_visited[neighbour]) {
            auto child_segment = DFS(neighbours, is_star, x, result_distance, is_visited, neighbour);
            if (child_segment.is_empty) {
                return Segment{0,0,true,false};
            }
            if (!child_segment.is_full) {
                max_of_min_values = std::max(child_segment.min_value, max_of_min_values);
                min_of_max_values = std::min(child_segment.max_value, min_of_max_values);
                is_restricted = true;
            }
        }
    }
    Segment new_segment;
    if (is_restricted) {
        if (max_of_min_values - result_distance <= min_of_max_values + result_distance) {
            new_segment = Segment{max_of_min_values - result_distance, min_of_max_values + result_distance, false, false};
        } else {
            return Segment{0, 0, true, false};
        }
    } else {
        new_segment = Segment{0, 0, false, true};
    }
    if (!is_star[current_node]) {
        if (!new_segment.is_empty && (new_segment.is_full || (x[current_node] >= new_segment.min_value && x[current_node] <= new_segment.max_value))) {
            new_segment = Segment{x[current_node], x[current_node], false, false};
        } else {
            new_segment = Segment{0, 0, true, false};
        }
    }
    return new_segment;
}

bool IsPossible(
    const std::vector<std::vector<int>>& neighbours,
    const std::vector<bool>& is_star,
    const std::vector<long double>& x,
    long double result_distance,
    const int n
) {
    std::vector<bool> is_visited(n, false);
    auto segment = DFS(neighbours, is_star, x, result_distance, is_visited, 0);
    return !segment.is_empty;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout << std::setprecision(20);
    int n;
    std::cin >> n;
    std::vector<long double> x(n);
    std::vector<bool> is_star(n, false);
    for (int i = 0; i < n; ++i) {
        std::string input_string;
        std::cin >> input_string;
        if (input_string[0] == '*') {
            is_star[i] = true;
        } else {
            is_star[i] = false;
            x[i] = std::stoll(input_string);
        }
    }
    std::vector<std::vector<int>> neighbours(n);
    for (int i = 0; i + 1 < n; ++i) {
        int first_node,second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        neighbours[first_node].push_back(second_node);
        neighbours[second_node].push_back(first_node);
    }
    long double left = 0;
    long double right = 10000001;
    while (right - left > 0.0000000001) {
        long double middle = (right + left) / 2;
        if (IsPossible(neighbours, is_star, x, middle, n)) {
            right = middle;
        } else {
            left = middle;
        }
    }
    printf("%.20Lf\n", right);
    return 0;
}
