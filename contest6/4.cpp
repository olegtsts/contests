#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include <cmath>

struct Point {
    long double x;
    long double y;

    Point(const long double x, const long double y)
    : x(x)
    , y(y)
    {}

    Point()
    : x(0)
    , y(0)
    {}
};

inline long double get_distance(const Point& first_edge, const Point& second_edge, const Point& point) {
    long double a = first_edge.y - second_edge.y;
    long double b = second_edge.x - first_edge.x;
    long double c = first_edge.x * second_edge.y - first_edge.y * second_edge.x;
    long double x = a * point.x + b * point.y + c;
    if (x < 0) {
        x = -x;
    }
    return x / sqrt(a * a + b * b);
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }
    long double min_distance = 1e10;
    for (size_t i = 0; i < n; ++i) {
        size_t prev_index = (n + i - 1) % n;
        size_t next_index = (n + i + 1) % n;
        long double distance = get_distance(points[prev_index], points[next_index], points[i]);
        if (min_distance > distance) {
            min_distance = distance;
        }
    }
    std::cout << std::setprecision(10) << min_distance / 2 << std::endl;

    return 0;
}
