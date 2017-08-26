#include <map>
#include <limits>
#include <algorithm>
#include <vector>
#include <iostream>

struct Linear {
    long long int a = 0;
    long long int b = 0;

    Linear& operator+=(const Linear& other) {
        a += other.a;
        b += other.b;
        return *this;
    }
    Linear& operator-=(const Linear& other) {
        a -= other.a;
        b -= other.b;
        return *this;
    }

    Linear operator-(const Linear& other) const {
        Linear new_object(*this);
        new_object -= other;
        return new_object;
    }

    Linear operator+(const Linear& other) const {
        Linear new_object(*this);
        new_object += other;
        return new_object;
    }
};

template <typename TX, typename TY, typename TValue>
struct Point {
    TX x;
    TY y;
    TValue value;
};

template <typename TX, typename TY, typename TValue>
class SquareNode {
public:
    using TPoint = Point<TX, TY, TValue>;

    SquareNode()
    {}

    void LoadPoints(std::vector<TPoint>& sorted_x_points, std::vector<TPoint>& sorted_y_points) {
        min_x = std::numeric_limits<TX>::max();
        max_x = std::numeric_limits<TX>::min();
        min_y = std::numeric_limits<TY>::max();
        max_y = std::numeric_limits<TY>::min();
        TValue prefix_sum;
        TX prev_x(std::numeric_limits<TX>::max());
        full_sum = TValue();
        for (auto& point: sorted_x_points) {
            if (min_x > point.x) {
                min_x = point.x;
            }
            if (max_x < point.x) {
                max_x = point.x;
            }
            if (min_y > point.y) {
                min_y = point.y;
            }
            if (max_y < point.y) {
                max_y = point.y;
            }
            if (prev_x != point.x && prev_x != std::numeric_limits<TX>::max()) {
                prefix_cols_sums[prev_x] = prefix_sum;
            }
            prefix_sum += point.value;
            prev_x = point.x;
            full_sum += point.value;
        }
        ++max_x;
        ++max_y;
        mid_x = (min_x + max_x) / 2;
        mid_y = (min_y + max_y) / 2;
        prefix_cols_sums[prev_x] = prefix_sum;
        prefix_sum = TValue{};
        TY prev_y(std::numeric_limits<TY>::max());
        for (auto& point: sorted_y_points) {
            if (prev_y != point.y && prev_y != std::numeric_limits<TY>::max()) {
                prefix_rows_sums[prev_y] = prefix_sum;
            }
            prefix_sum += point.value;
            prev_y = point.y;
        }
        prefix_rows_sums[prev_y] = prefix_sum;
    }

    bool IsEmpty() const noexcept {
        return max_x == min_x || max_y == min_y || prefix_rows_sums.size() == 0;
    }

    bool IsDivisable() const noexcept {
        return max_x > min_x + 1 && max_y > min_y + 1;
    }

    template <typename TCoord>
    TValue GetPrefixSum(const TCoord& coord, const std::map<TCoord, TValue>& mapping) {
        if (IsEmpty()) {
            return {};
        } else {
            auto it = mapping.lower_bound(coord);
            if (it == mapping.begin()) {
                return {};
            } else {
                --it;
                return it->second;
            }
        }
    }

    TValue GetPrefixColSum(TX x) {
        return GetPrefixSum(x, prefix_cols_sums);
    }

    TValue GetPrefixRowSum(TY y) {
        return GetPrefixSum(y, prefix_rows_sums);
    }

    TValue GetPrefixSquareSum(TX x, TY y) {
        if (IsEmpty()) {
            return {};
        }
        if (x >= max_x) {
            x = max_x;
        }
        if (y >= max_y) {
            y = max_y;
        }
        if (x <= min_x || y <= min_y) {
            return {};
        }
        if (x == max_x && y == max_y) {
            return full_sum;
        } else if (x == max_x) {
            return GetPrefixRowSum(y);
        } else if (y == max_y) {
            return GetPrefixColSum(x);
        }
        TValue result;
        for (SquareNode* pointer: {left_lower, left_upper, right_lower, right_upper}) {
            if (pointer) {
                result += pointer->GetPrefixSquareSum(x, y);
            }
        }
        return result;
    }
public:
    TX min_x = 0;
    TX max_x = 0;
    TY min_y = 0;
    TY max_y = 0;
    TX mid_x = 0;
    TY mid_y = 0;

    TValue full_sum;

    SquareNode* left_lower;
    SquareNode* right_lower;
    SquareNode* left_upper;
    SquareNode* right_upper;
private:
    std::map<TY, TValue> prefix_rows_sums;
    std::map<TX, TValue> prefix_cols_sums;
};

using TPoint = Point<int, long long int, Linear>;
using TSquareNode = SquareNode<int, long long int, Linear>;

TSquareNode* BuildTree(std::vector<TSquareNode>& pool, int& pool_index, std::vector<TPoint>& sorted_x_points,
                       std::vector<TPoint>& sorted_y_points) {
    TSquareNode& node = pool[pool_index++];
    if (sorted_x_points.size() > 0) {
        node.LoadPoints(sorted_x_points, sorted_y_points);
        if (node.max_x > node.min_x + 1 && node.max_y > node.min_y + 1) {
            std::vector<TPoint> sorted_x_left_lower_points;
            std::vector<TPoint> sorted_x_right_upper_points;
            std::vector<TPoint> sorted_x_left_upper_points;
            std::vector<TPoint> sorted_x_right_lower_points;
            std::vector<TPoint> sorted_y_left_lower_points;
            std::vector<TPoint> sorted_y_right_upper_points;
            std::vector<TPoint> sorted_y_left_upper_points;
            std::vector<TPoint> sorted_y_right_lower_points;

            sorted_x_left_lower_points.reserve(sorted_x_points.size());
            sorted_x_right_lower_points.reserve(sorted_x_points.size());
            sorted_x_left_upper_points.reserve(sorted_x_points.size());
            sorted_x_right_upper_points.reserve(sorted_x_points.size());
            sorted_y_left_lower_points.reserve(sorted_x_points.size());
            sorted_y_right_lower_points.reserve(sorted_x_points.size());
            sorted_y_left_upper_points.reserve(sorted_x_points.size());
            sorted_y_right_upper_points.reserve(sorted_x_points.size());
            for (auto& point: sorted_x_points) {
                if (point.x < node.mid_x && point.y < node.mid_y) {
                    sorted_x_left_lower_points.push_back(point);
                } else if (point.x < node.mid_x && point.y >= node.mid_y) {
                    sorted_x_left_upper_points.push_back(point);
                } else if (point.x >= node.mid_x && point.y < node.mid_y) {
                    sorted_x_right_lower_points.push_back(point);
                } else {
                    sorted_x_right_upper_points.push_back(point);
                }
            }
            for (auto& point: sorted_y_points) {
                if (point.x < node.mid_x && point.y < node.mid_y) {
                    sorted_y_left_lower_points.push_back(point);
                } else if (point.x < node.mid_x && point.y >= node.mid_y) {
                    sorted_y_left_upper_points.push_back(point);
                } else if (point.x >= node.mid_x && point.y < node.mid_y) {
                    sorted_y_right_lower_points.push_back(point);
                } else {
                    sorted_y_right_upper_points.push_back(point);
                }
            }

            node.left_lower = BuildTree(pool, pool_index, sorted_x_left_lower_points, sorted_y_left_lower_points);
            node.left_upper = BuildTree(pool, pool_index, sorted_x_left_upper_points, sorted_y_left_upper_points);
            node.right_lower = BuildTree(pool, pool_index, sorted_x_right_lower_points, sorted_y_right_lower_points);
            node.right_upper = BuildTree(pool, pool_index, sorted_x_right_upper_points, sorted_y_right_upper_points);
        } else if (node.max_x > node.min_x + 1) {
            std::vector<TPoint> sorted_x_left_lower_points;
            std::vector<TPoint> sorted_x_right_lower_points;
            std::vector<TPoint> sorted_y_left_lower_points;
            std::vector<TPoint> sorted_y_right_lower_points;

            sorted_x_left_lower_points.reserve(sorted_x_points.size());
            sorted_x_right_lower_points.reserve(sorted_x_points.size());
            sorted_y_left_lower_points.reserve(sorted_x_points.size());
            sorted_y_right_lower_points.reserve(sorted_x_points.size());
            for (auto& point: sorted_x_points) {
                if (point.x < node.mid_x) {
                    sorted_x_left_lower_points.push_back(point);
                } else if (point.x >= node.mid_x) {
                    sorted_x_right_lower_points.push_back(point);
                }
            }
            for (auto& point: sorted_y_points) {
                if (point.x < node.mid_x) {
                    sorted_y_left_lower_points.push_back(point);
                } else if (point.x >= node.mid_x) {
                    sorted_y_right_lower_points.push_back(point);
                }
            }
            node.left_lower = BuildTree(pool, pool_index, sorted_x_left_lower_points, sorted_y_left_lower_points);
            node.right_lower = BuildTree(pool, pool_index, sorted_x_right_lower_points, sorted_y_right_lower_points);
        } else if (node.max_y > node.min_y + 1) {
            std::vector<TPoint> sorted_x_left_lower_points;
            std::vector<TPoint> sorted_x_left_upper_points;
            std::vector<TPoint> sorted_y_left_lower_points;
            std::vector<TPoint> sorted_y_left_upper_points;

            sorted_x_left_lower_points.reserve(sorted_x_points.size());
            sorted_x_left_upper_points.reserve(sorted_x_points.size());
            sorted_y_left_lower_points.reserve(sorted_x_points.size());
            sorted_y_left_upper_points.reserve(sorted_x_points.size());

            for (auto& point: sorted_x_points) {
                if (point.y < node.mid_y) {
                    sorted_x_left_lower_points.push_back(point);
                } else if (point.y >= node.mid_y) {
                    sorted_x_left_upper_points.push_back(point);
                }
            }
            for (auto& point: sorted_y_points) {
                if (point.y < node.mid_y) {
                    sorted_y_left_lower_points.push_back(point);
                } else if (point.y >= node.mid_y) {
                    sorted_y_left_upper_points.push_back(point);
                }
            }
            node.left_lower = BuildTree(pool, pool_index, sorted_x_left_lower_points, sorted_y_left_lower_points);
            node.left_upper = BuildTree(pool, pool_index, sorted_x_left_upper_points, sorted_y_left_upper_points);
        }
    }
    return &node;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<TPoint> points(2 * n);
    std::vector<TPoint> sorted_x_points(2 * n);
    std::vector<TPoint> sorted_y_points(2 * n);
//    auto start_time = std::chrono::system_clock::now();
    std::vector<long long int> constant_prefix_sums(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        long long int x1, x2, y1, y2, a, b;
        std::cin >> x1 >> x2 >> y1 >> a >> b >> y2;
        sorted_x_points[2 * i] = {i, x1, {a, b - y1}};
        sorted_x_points[2 * i + 1] = {i, x2, {-a, y2 - b}};
        sorted_y_points[2 * i] = {i, x1, {a, b - y1}};
        sorted_y_points[2 * i + 1] = {i, x2, {-a, y2 - b}};
        constant_prefix_sums[i + 1] = y1;
        constant_prefix_sums[i + 1] += constant_prefix_sums[i];
    }
    std::sort(sorted_x_points.begin(), sorted_x_points.end(), [] (const TPoint& first, const TPoint& second) -> bool {
        return first.x < second.x;
    });
    std::sort(sorted_y_points.begin(), sorted_y_points.end(), [] (const TPoint& first, const TPoint& second) -> bool {
        return first.y < second.y;
    });

//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << '\n';
//    start_time = std::chrono::system_clock::now();
    std::vector<TSquareNode> pool(2000000);
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << '\n';
//    start_time = std::chrono::system_clock::now();
    int pool_index = 0;
    TSquareNode& root = *BuildTree(pool, pool_index, sorted_x_points, sorted_y_points);
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << '\n';
//    start_time = std::chrono::system_clock::now();
    int m;
    std::cin >> m;
    long long int last = 0;
    for (int i = 0; i < m; ++i) {
        int l, r;
        long long int x;
        std::cin >> l >> r >> x;
        --l;
        --r;
        x += last;
        x %= 1000000000;
        long long int initial_constant = constant_prefix_sums[r + 1] - constant_prefix_sums[l];
        Linear first_linear = root.GetPrefixSquareSum(r + 1, x);
        Linear second_linear = root.GetPrefixSquareSum(l, x);
        Linear linear = first_linear - second_linear;
        linear.b += initial_constant;
        last = linear.a * x + linear.b;
        std::cout << last << std::endl;
    }
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << '\n';
//    start_time = std::chrono::system_clock::now();


    return 0;
}
