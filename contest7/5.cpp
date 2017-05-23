#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
    long double x;
    long double y;

    Point()
    : x(0)
    , y(0)
    {}

    Point(const long double x, const long double y)
    : x(x)
    , y(y)
    {}
};

struct Line {
    Point first;
    Point second;

    Line() {}
    Line(const Point& first, const Point& second)
    : first(first)
    , second(second)
    {}
};

long double calc_vector_product(const Line& line, const Point& point) {
    return (line.first.x - point.x) * (line.second.y - point.y) - (line.first.y - point.y) * (line.second.x - point.x);
}

long double calc_cos(const Line& line, const Point& point) {
    return (
            (line.first.x - point.x) * (line.second.x - point.x) + (line.first.y - point.y) * (line.second.y - point.y)\
        ) / sqrt(
            (line.first.x - point.x) * (line.first.x - point.x) + (line.first.y - point.y) * (line.first.y - point.y)
        ) / sqrt(
            (line.second.x - point.x) * (line.second.x - point.x) + (line.second.y - point.y) * (line.second.y - point.y)
        );
}

long double get_distance_squared(const Point& first_point, const Point& second_point) {
    return (first_point.x - second_point.x) * (first_point.x - second_point.x) + (first_point.y - second_point.y) * (first_point.y - second_point.y);
}

Point get_central_point(const Point& first, const Point& second, const Point& third) {
    long double z_x = (first.y - second.y) * (third.x * third.x + third.y * third.y) + (second.y - third.y) * (first.x * first.x + first.y * first.y) + (third.y - first.y) * (second.x * second.x + second.y * second.y);
    long double z_y = (first.x - second.x) * (third.x * third.x + third.y * third.y) + (second.x - third.x) * (first.x * first.x + first.y * first.y) + (third.x - first.x) * (second.x * second.x + second.y * second.y);
    long double z = (first.x - second.x) *  (third.y - first.y) -  (first.y - second.y) * (third.x - first.x);

    return Point(-z_x/z/2, z_y /z/2);
}

int main () {
    int w;
    std::cin >> w;
    std::vector<Point> white_points(w);
    for (size_t i = 0; i < w; ++i) {
        std::cin >> white_points[i].x >> white_points[i].y;
    }
    int r;
    std::cin >> r;
    std::vector<Point> red_points(r);
    for (size_t i = 0; i < r; ++i) {
        std::cin >> red_points[i].x >> red_points[i].y;
    }
    int max_points_number = 0;
    for (size_t i = 0; i < w; ++i) {
        for (size_t k = i + 1; k < w; ++k) {
//            std::cout << "start i = " << i << ", k = " << k << std::endl;
            Line white_line(white_points[i], white_points[k]);
            std::vector<long double> above_cos;
            std::vector<long double> below_cos;

            for (size_t d = 0; d < r; ++d) {
                Point red_point = red_points[d];
                long double cos_value = calc_cos(white_line, red_point);
                long double vector_product = calc_vector_product(white_line, red_point);
//                std::cout << "cos_value of point " << d << " is " << cos_value << std::endl;
                if (vector_product > 0) {
//                    std::cout << "red point " << d << " is above" << std::endl;
                    above_cos.push_back(cos_value);
                } else {
//                    std::cout << "red point " << d << " is below" << std::endl;
                    below_cos.push_back(cos_value);
                }
            }
            std::sort(above_cos.begin(), above_cos.end());
            std::sort(below_cos.begin(), below_cos.end());

//            std::cout << "above_cos = ";
//            for (auto& el: above_cos) {
//                std::cout << el << " ";
//            }
//            std::cout << std::endl;
//
//            std::cout << "below_cos = ";
//            for (auto& el: below_cos) {
//                std::cout << el << " ";
//            }
//            std::cout << std::endl;


            for (size_t j = k + 1; j < w; ++j) {
                Point white_point = white_points[j];
                long double cos_value = calc_cos(white_line, white_point);
                long double vector_product = calc_vector_product(white_line, white_point);
                if (vector_product != 0) {
                    int cur_points_number = 0;
                    if (vector_product > 0) {
                        cur_points_number += std::lower_bound(above_cos.begin(), above_cos.end(), cos_value) - above_cos.begin();
                        cur_points_number += std::lower_bound(below_cos.begin(), below_cos.end(), -cos_value) - below_cos.begin();
                    } else {
                        cur_points_number += std::lower_bound(above_cos.begin(), above_cos.end(), -cos_value) - above_cos.begin();
                        cur_points_number += std::lower_bound(below_cos.begin(), below_cos.end(), cos_value) - below_cos.begin();
                    }
    //                std::cout << "i = " << i << " k = " << k << " j = " << j << " cos_vlaue = " << cos_value << " cur_points_number = " << cur_points_number << std::endl;

                    if (max_points_number < cur_points_number) {
                        max_points_number = cur_points_number;
                    }
                }
            }
        }
    }
    std::cout << max_points_number << std::endl;
    return 0;
}
