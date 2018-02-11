#include <iostream>

struct Point {
    long long int x;
    long long int y;


    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};
struct LinedPoints {
    bool is_first_initialized = false;
    bool is_second_initialized = false;
    bool is_on_same_line = true;
    Point first_point;
    Point second_point;

    void AddPoint(const Point& point) {
        if (!is_first_initialized) {
            first_point = point;
            is_first_initialized = true;
        } else if (!is_second_initialized) {
            if (point != first_point) {
                second_point = point;
                is_second_initialized = true;
            } else {
                // Do nothing
            }
        } else {
            if ((point.x - first_point.x) * (second_point.y - first_point.y) ==
                (point.y - first_point.y) * (second_point.x - first_point.x)) {
                //Everything is fine
            } else {
                is_on_same_line = false;
            }
        }
    }
    bool IsOnSameLine() const {
        return is_on_same_line;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    long long int n;
    std::cin >> n;
    LinedPoints lined_points;
    for (long long int i = 0; i < n; ++i) {
        int type ;
        std::cin >> type;
        if (type == 0) {
            long long int r,x,y;
            std::cin >> r >> x >> y;
            lined_points.AddPoint({2 * x, 2 * y});
        } else {
            long long int x1,y1,x2,y2,x3,y3,x4,y4;
            std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
            lined_points.AddPoint({x1 + x3, y1 + y3});
        }
        if (!lined_points.IsOnSameLine()) {
            std::cout << "No\n";
            return 0;
        }
    }
    std::cout << "Yes\n";
    return 0;
}
