#include <map>
#include <limits>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>

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

    void StoreMinMaxValues(const std::vector<TPoint>& points) {
        min_x = std::numeric_limits<TX>::max();
        max_x = std::numeric_limits<TX>::min();
        min_y = std::numeric_limits<TY>::max();
        max_y = std::numeric_limits<TY>::min();
        full_sum = TValue();
        any_points = false;
        for (auto& point: points) {
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
            full_sum += point.value;
            any_points = true;
        }
        ++max_x;
        ++max_y;
        mid_x = (min_x + max_x) / 2;
        mid_y = (min_y + max_y) / 2;
    }

    void LoadPoints(std::vector<TPoint>& points) {
        StoreMinMaxValues(points);
        if (is_cols_index) {
            std::sort(points.begin(), points.end(), [] (const TPoint& first, const TPoint& second) -> bool {
                return first.x < second.x;
            });
            TValue prefix_sum;
            size_t prev_index{0};
            prefix_cols_sums.resize(static_cast<size_t>(max_x - min_x), {});
            for (auto& point: points) {
                while (prev_index < static_cast<size_t>(point.x - min_x)) {
                    prefix_cols_sums[prev_index++] = prefix_sum;
                }
                prefix_sum += point.value;
            }
        }

        if (is_rows_index) {
            std::sort(points.begin(), points.end(), [] (const TPoint& first, const TPoint& second) -> bool {
                return first.y < second.y;
            });
            TValue prefix_sum;
            size_t prev_index{0};
            prefix_rows_sums.resize(static_cast<size_t>(max_y - min_y), {});
            for (auto& point: points) {
                while (prev_index < static_cast<size_t>(point.y - min_y)) {
                    prefix_rows_sums[prev_index++] = prefix_sum;
                }
                prefix_sum += point.value;
            }
        }
    }


    bool IsEmpty() const noexcept {
        return max_x == min_x || max_y == min_y || !any_points;
    }

    bool IsDivisable() const noexcept {
        return max_x > min_x + 1 && max_y > min_y + 1;
    }

    template <typename TCoord>
    TValue GetMapPrefixSum(const TCoord& coord, const std::map<TCoord, TValue>& mapping) {
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

    template <typename TCoord>
    TValue GetVectorPrefixSum(const TCoord& coord, const std::vector<TValue>& prefix_sums, const TCoord& min_coord) const {
        if (prefix_sums.size() == 0) {
            return {};
        }
        size_t index = static_cast<size_t>(coord - min_coord - 1);
        if (index >= prefix_sums.size()) {
            auto it = prefix_sums.end();
            --it;
            return *it;
        }
        return prefix_sums[index];
    }

    TValue GetPrefixColSum(TX x) const {
        return GetVectorPrefixSum(x, prefix_cols_sums, min_x);
    }

    TValue GetPrefixRowSum(TY y) const {
        return GetVectorPrefixSum(y, prefix_rows_sums, min_y);
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
        } else if (x == max_x && is_rows_index) {
            return GetPrefixRowSum(y);
        } else if (y == max_y && is_cols_index) {
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

    SquareNode* left_lower = nullptr;
    SquareNode* right_lower = nullptr;
    SquareNode* left_upper = nullptr;
    SquareNode* right_upper = nullptr;

    bool is_rows_index = true;
    bool is_cols_index = true;

    bool any_points;
private:
    std::vector<TValue> prefix_rows_sums;
    std::vector<TValue> prefix_cols_sums;
};

using TPoint = Point<int, long long int, Linear>;
using TSquareNode = SquareNode<int, long long int, Linear>;

TSquareNode* BuildTree(const bool is_rows_index, const bool is_cols_index, std::vector<TSquareNode>& pool, int& pool_index, std::vector<TPoint>& points) {
    TSquareNode& node = pool[pool_index++];
    assert(static_cast<size_t>(pool_index) < pool.size());
    if (points.size() > 0) {
        node.is_rows_index = is_rows_index;
        node.is_cols_index = is_cols_index;
        node.LoadPoints(points);
        if (node.max_x > node.min_x + 1 && node.max_y > node.min_y + 1) {
            std::vector<TPoint> left_lower_points;
            std::vector<TPoint> right_upper_points;
            std::vector<TPoint> left_upper_points;
            std::vector<TPoint> right_lower_points;
            left_lower_points.reserve(points.size());
            right_lower_points.reserve(points.size());
            left_upper_points.reserve(points.size());
            right_upper_points.reserve(points.size());
            for (auto& point: points) {
                if (point.x < node.mid_x && point.y < node.mid_y) {
                    left_lower_points.push_back(point);
                } else if (point.x < node.mid_x && point.y >= node.mid_y) {
                    left_upper_points.push_back(point);
                } else if (point.x >= node.mid_x && point.y < node.mid_y) {
                    right_lower_points.push_back(point);
                } else {
                    right_upper_points.push_back(point);
                }
            }
            node.left_lower = BuildTree(true, true, pool, pool_index, left_lower_points);
            node.left_upper = BuildTree(true, false, pool, pool_index, left_upper_points);
            node.right_lower = BuildTree(false, true, pool, pool_index, right_lower_points);
            node.right_upper = BuildTree(false, false, pool, pool_index, right_upper_points);
        } else if (node.max_x > node.min_x + 1) {
            std::vector<TPoint> left_lower_points;
            std::vector<TPoint> right_lower_points;
            for (auto& point: points) {
                if (point.x < node.mid_x) {
                    left_lower_points.push_back(point);
                } else if (point.x >= node.mid_x) {
                    right_lower_points.push_back(point);
                }
            }
            node.left_lower = BuildTree(true, false, pool, pool_index, left_lower_points);
            node.right_lower = BuildTree(false, false, pool, pool_index, right_lower_points);
        } else if (node.max_y > node.min_y + 1) {
            std::vector<TPoint> left_lower_points;
            std::vector<TPoint> left_upper_points;
            for (auto& point: points) {
                if (point.y < node.mid_y) {
                    left_lower_points.push_back(point);
                } else if (point.y >= node.mid_y) {
                    left_upper_points.push_back(point);
                }
            }
            node.left_lower = BuildTree(false, true, pool, pool_index, left_lower_points);
            node.left_upper = BuildTree(false, false, pool, pool_index, left_upper_points);
        }
    }
    return &node;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<TPoint> points(2 * n);
//    auto start_time = std::chrono::system_clock::now();
    std::vector<long long int> constant_prefix_sums(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        long long int x1, x2, y1, y2, a, b;
        std::cin >> x1 >> x2 >> y1 >> a >> b >> y2;
        points[2 * i] = {i, x1, {a, b - y1}};
        points[2 * i + 1] = {i, x2, {-a, y2 - b}};
        constant_prefix_sums[i + 1] = y1;
        constant_prefix_sums[i + 1] += constant_prefix_sums[i];
    }
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << '\n';
//    start_time = std::chrono::system_clock::now();
    std::vector<TSquareNode> pool(2000000);
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << '\n';
//    start_time = std::chrono::system_clock::now();
    int pool_index = 0;
    TSquareNode& root = *BuildTree(false, false, pool, pool_index, points);
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
