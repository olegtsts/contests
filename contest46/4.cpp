#include <iostream>
#include <vector>
#include <tuple>

struct Point {
    long long int x;
    long long int y;

    bool operator==(const Point& other) const {
        return std::forward_as_tuple(x, y) == std::forward_as_tuple(other.x, other.y);
    }
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

bool ArePointsOnTheSameLine(const Point& first_point, const Point& second_point, const Point& third_point) {
    return (second_point.x - first_point.x) * (third_point.y - first_point.y) == (second_point.y - first_point.y) * (third_point.x - first_point.x);
}

bool IsFirstCaseOK(const int n, const Point& first_point, const Point& second_point, const Point& third_point, const std::vector<Point>& points) {
    // First case: line of 1st point contains 2nd point
    // Find 4th point not on line between 1 and 2 and not equal 3 point
    int forth_point_index = -1;
    for (int i = 2; i < n; ++i) {
        if (points[i] != third_point) {
            if (!ArePointsOnTheSameLine(first_point, second_point, points[i])) {
                forth_point_index = i;
                break;
            }
        }
    }
    if (forth_point_index == -1) {
        return true;
    }
    //Now check that all points are either on 1-2 or on 3-4
    for (int i = 0; i < n; ++i) {
        if (!ArePointsOnTheSameLine(first_point, second_point, points[i]) && !ArePointsOnTheSameLine(third_point, points[forth_point_index], points[i])) {
            return false;
        }
    }
    return true;
}



int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }

    if (n <= 4) {
        std::cout << "YES\n";
        return 0;
    }

    auto first_point = points[0];
    auto second_point = points[1];
    Point third_point;
    bool third_point_found = false;
    for (int i = 2; i < n; ++i) {
        if (!ArePointsOnTheSameLine(first_point, second_point, points[i])) {
            third_point = points[i];
            third_point_found = true;
            break;
        }
    }
    if (!third_point_found) {
        std::cout << "YES\n";
        return 0;
    }

    if (
        IsFirstCaseOK(n, first_point, second_point, third_point, points)
        || IsFirstCaseOK(n, first_point, third_point, second_point, points)
        || IsFirstCaseOK(n, second_point, third_point, first_point, points)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
