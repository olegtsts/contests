#include <iostream>
#include <vector>
#include <algorithm>

struct Vector {
    long long int x;
    long long int y;

    long long int GetCrossProduct(const Vector& other) const {
        return x * other.y - y * other.x;
    }
    long long int GetScalarProduct(const Vector& other) const {
        return x * other.x + y * other.y;
    }
};

struct Point {
    long long int x;
    long long int y;

    Vector Subtract(const Point& other) const {
        return {x - other.x, y - other.y};
    }
};

struct Segment {
    Point first_point;
    Point second_point;

    bool DoSegmentsIntersect(const Segment& other) const {
        auto p = first_point;
        auto q = other.first_point;
        auto r = second_point.Subtract(first_point);
        auto s = other.second_point.Subtract(other.first_point);
        auto product = r.GetCrossProduct(s);
        if (product != 0) {
            long long int t = (q.Subtract(p).GetCrossProduct(s));
            long long int u = (q.Subtract(p).GetCrossProduct(r));
            if (product < 0) {
                product = -product;
                t = -t;
                u = -u;
            }
            return 0 <= t && t <= product && 0 <= u && u <= product;
        } else {
            if (q.Subtract(p).GetCrossProduct(r) == 0) {
                auto t0 = q.Subtract(p).GetScalarProduct(r);
                auto t1 = other.second_point.Subtract(p).GetScalarProduct(r);
                if (t0 < 0 && t1 < 0) {
                    return false;
                } else if (t0 > r.GetScalarProduct(r) && t1 > r.GetScalarProduct(r)) {
                    return false;
                } else {
                    return true;
                }
            } else {
                return false;
            }
        }
    }
};

bool DoesOkChoiceExist(
    std::vector<Point>& rebels,
    std::vector<Point>& bases,
    const size_t processed_rebels,
    std::vector<Segment>& segments
) {
    if (processed_rebels >= rebels.size()) {
        return true;
    }
    for (size_t i = processed_rebels; i < bases.size(); ++i) {
        std::swap(bases[i], bases[processed_rebels]);
        bool is_good_option = true;
        for (auto& segment: segments) {
            if (segment.DoSegmentsIntersect({rebels[processed_rebels], bases[processed_rebels]})) {
                is_good_option = false;
                break;
            }
        }
        segments.push_back({rebels[processed_rebels], bases[processed_rebels]});
        if (is_good_option && DoesOkChoiceExist(rebels, bases, processed_rebels + 1, segments)) {
            return true;
        }
        segments.pop_back();
        std::swap(bases[i], bases[processed_rebels]);
    }
    return false;
}

int main() {
    int r,b;
//    std::cout << std::boolalpha << Segment{Point{1,1},Point{2,2}}.DoSegmentsIntersect({Point{2,2}, Point{3,3}}) <<std::endl;
    std::cin >> r >> b;
    if (r != b) {
        std::cout << "No\n";
        return 0;
    }
    std::vector<Point> rebels(r);
    std::vector<Point> bases(b);
    for (int i = 0; i < r; ++i) {
        std::cin >> rebels[i].x >> rebels[i].y;
    }
    for (int i = 0; i < b; ++i) {
        std::cin >> bases[i].x >> bases[i].y;
    }
    std::vector<Segment> segments;
    if (DoesOkChoiceExist(rebels, bases, 0, segments)) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    return 0;
}
