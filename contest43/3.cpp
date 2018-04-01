#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>

const long double EPSILON = 0.00001;

bool AreDoublesClose(const long double first_number, const long double second_number) {
    return fabs(first_number - second_number) < EPSILON;
}

enum class IntersectionType {INTERSECT = 0, ADJACENT = 1, NO_INTERSECTION = 2};

struct Point {
    long double x;
    long double y;

    long double GetDitance(const Point& other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }

    bool ArePointsClose(const Point& other) const {
        return AreDoublesClose(x, other.x) && AreDoublesClose(y, other.y);
    }

    bool operator<(const Point& other) const {
        return std::forward_as_tuple(x, y) < std::forward_as_tuple(other.x, other.y);
    }
};

struct Circle {
    Point center;
    long double radius;

    IntersectionType GetIntersectionType(const Circle& other) const {
        int distance_squared = (center.x - other.center.x) * (center.x - other.center.x) + (center.y - other.center.y) * (center.y - other.center.y);
        int sum_of_radii_squared = (radius + other.radius) * (radius + other.radius);
        if (distance_squared == sum_of_radii_squared) {
            return IntersectionType::ADJACENT;
        } else if (distance_squared > sum_of_radii_squared) {
            return IntersectionType::NO_INTERSECTION;
        } else {
            int difference_of_radii_squared = (radius - other.radius) * (radius - other.radius);
            if (difference_of_radii_squared == distance_squared) {
                return IntersectionType::ADJACENT;
            } else if (difference_of_radii_squared < distance_squared) {
                return IntersectionType::INTERSECT;
            } else {
                return IntersectionType::NO_INTERSECTION;
            }
        }
    }

    std::vector<Point> GetIntersectionPoints(const Circle& other) const {
        long double d = center.GetDitance(other.center);
        if (d > radius + other.radius) {
            return {};
        }
        if (d < fabs(radius - other.radius)) {
            return {};
        }
        if (d == 0) {
            return {};
        }
        long double a = (radius * radius - other.radius * other.radius + d * d) / (2 * d);
        long double h = sqrt(radius * radius - a * a);
        Point p2{center.x + a * (other.center.x - center.x) / d,
            center.y + a * (other.center.y - center.y) / d};
        std::vector<Point> result_points = {
            {
                p2.x + h * (other.center.y - center.y) / d,
                p2.y - h * (other.center.x - center.x) / d
            },
            {
                p2.x - h * (other.center.y - center.y) / d,
                p2.y + h * (other.center.x - center.x) / d
            }
        };
        if (h < EPSILON) {
            result_points.pop_back();
        }
        std::sort(result_points.begin(), result_points.end());
        return result_points;
    }
};

struct Intersection {
    IntersectionType type;
    int first_index;
    int second_index;

    bool operator<(const Intersection& other) const {
        return std::forward_as_tuple(type, first_index, second_index) < std::forward_as_tuple(other.type, other.first_index, other.second_index);
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Circle> circles(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> circles[i].center.x >> circles[i].center.y >> circles[i].radius;
    }
    std::vector<Intersection> intersections;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            intersections.push_back({circles[i].GetIntersectionType(circles[j]), i, j});
        }
    }
    int intersections_count;
    if (n == 0) {
        intersections_count = 1;
    } else if (n == 1) {
        intersections_count = 2;
    } else if (n == 2) {
        if (intersections[0].type == IntersectionType::INTERSECT) {
            intersections_count = 4;
        } else {
            intersections_count = 3;
        }
    } else if (n == 3) {
        std::sort(intersections.begin(), intersections.end());
        if (intersections[0].type == IntersectionType::INTERSECT) {
            if (intersections[1].type == IntersectionType::INTERSECT) {
                if (intersections[2].type == IntersectionType::INTERSECT) {
                    intersections_count = 8;
                } else if (intersections[2].type == IntersectionType::ADJACENT) {
                    intersections_count = 7;
                } else {
                    intersections_count = 6;
                }
            } else if (intersections[1].type == IntersectionType::ADJACENT) {
                if (intersections[2].type == IntersectionType::ADJACENT) {
                    intersections_count = 6;
                } else {
                    intersections_count = 5;
                }
            } else {
                intersections_count = 5;
            }
        } else if (intersections[0].type == IntersectionType::ADJACENT
                   && intersections[1].type == IntersectionType::ADJACENT
                   && intersections[2].type == IntersectionType::ADJACENT
        ) {
            intersections_count = 5;
        } else {
            intersections_count = 4;
        }
    }
    if (n == 3
        && intersections[0].type != IntersectionType::NO_INTERSECTION
        && intersections[1].type != IntersectionType::NO_INTERSECTION
        && intersections[2].type != IntersectionType::NO_INTERSECTION
    ) {
        auto first_intersection_points = circles[0].GetIntersectionPoints(circles[1]);
        auto second_intersection_points = circles[1].GetIntersectionPoints(circles[2]);
        auto third_intersection_points = circles[2].GetIntersectionPoints(circles[0]);

        std::vector<Point> intersections;
        int same_intersection_points_count = 0;
        for (int i = 0; i < 2; ++i) {
            for (auto intersection: circles[i].GetIntersectionPoints(circles[(i + 1) % 3])) {
                bool intersection_already_mentioned = false;
                for (auto prev_intersection : intersections) {
                    if (prev_intersection.ArePointsClose(intersection)) {
                        intersection_already_mentioned = true;
                        break;
                    }
                }
                if (!intersection_already_mentioned) {
                    intersections.push_back(intersection);
                } else {
                    ++same_intersection_points_count;
                }
            }
        }
        intersections_count -= same_intersection_points_count;
    }
    std::cout << intersections_count << std::endl;
    return 0;
}
