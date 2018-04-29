#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

struct Point {
    long long int x;
    long long int y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};
namespace std {
  template <>
  struct hash<Point>
  {
    std::size_t operator()(const Point& k) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<long long int>()(k.x)
               ^ (hash<long long int>()(k.y))));
    }
  };
}
struct PointStorage {
    long long int total_count = 0;
    std::unordered_map<Point, long long int> point_count;
    std::unordered_map<long long int, std::unordered_map<Point, long long int>> x_coord_point_count;
    std::unordered_map<long long int, std::unordered_map<Point, long long int>> y_coord_point_count;
    std::unordered_map<long long int, long long int> x_coord_count;
    std::unordered_map<long long int, long long int> y_coord_count;

    template <typename Key>
    void UpdateMapping(std::unordered_map<Key, long long int>& mapping, const Key& key, const long long int sign) {
        if (mapping.count(key) == 0) {
            mapping[key] = 0;
        }
        mapping[key] += sign;
        if (mapping[key] == 0) {
            mapping.erase(key);
        }
    }

    void UpdateCoordMapping(std::unordered_map<long long int, std::unordered_map<Point, long long int>>& coord_point_count,
                            const long long int coord_value,
                            const Point& point,
                            const long long int sign)  {
        if (coord_point_count.count(coord_value) == 0) {
            coord_point_count[coord_value] = {};
        }
        UpdateMapping(coord_point_count[coord_value], point, sign);
        if (coord_point_count[coord_value].size() == 0) {
            coord_point_count.erase(coord_value);
        }
    }

    void AddPointWithSign(const Point& point, const long long int sign) {
        total_count += sign;
        UpdateMapping(point_count, point, sign);
        UpdateCoordMapping(x_coord_point_count, point.x, point, sign);
        UpdateCoordMapping(y_coord_point_count, point.y, point, sign);
        UpdateMapping(x_coord_count, point.x, sign);
        UpdateMapping(y_coord_count, point.y, sign);
    }

    void AddPoint(const Point& point) {
        AddPointWithSign(point, 1);
    }

    void RemovePoint(const Point & point) {
        AddPointWithSign(point, -1);
    }

    bool CheckXAdnY(const long long int x, const long long int y) {
        long long int common = 0;
        if (point_count.count({x, y}) > 0){
            common = point_count[{x, y}];
        }
        return x_coord_count[x] + y_coord_count[y] - common == total_count;
    }

    bool IsCoveredByTwoSegmentsWithX(const long long int x) {
        auto it = x_coord_point_count.begin();
        if (it->first == x) {
            ++it;
        }
        Point another_x_any_point = it->second.begin()->first;
        long long int y = another_x_any_point.y;
        return CheckXAdnY(x, y);
    }
    bool IsCoveredByTwoSegmentsWithY(const long long int y) {
        auto it = y_coord_point_count.begin();
        if (it->first == y) {
            ++it;
        }
        Point another_y_any_point = it->second.begin()->first;
        long long int x = another_y_any_point.x;
        return CheckXAdnY(x, y);
    }

    bool IsCoveredByTwoSegments() {
        if (point_count.size() <= 2) {
            return true;
        }
        if (x_coord_point_count.size() <= 1) {
            return true;
        }
        if (y_coord_point_count.size() <= 1) {
            return true;
        }
        auto it = point_count.begin();
        auto first_point = it->first;
        ++it;
        auto second_point = it->first;
        ++it;
        auto third_point = it->first;
        if (first_point.x == second_point.x) {
            return IsCoveredByTwoSegmentsWithX(first_point.x);
        } else if (first_point.x == third_point.x) {
            return IsCoveredByTwoSegmentsWithX(first_point.x);
        } else if (second_point.x == third_point.x) {
            return IsCoveredByTwoSegmentsWithX(second_point.x);
        } else if (first_point.y == second_point.y) {
            return IsCoveredByTwoSegmentsWithY(first_point.y);
        } else if (first_point.y == third_point.y) {
            return IsCoveredByTwoSegmentsWithY(first_point.y);
        } else if (second_point.y == third_point.y) {
            return IsCoveredByTwoSegmentsWithY(second_point.y);
        } else {
            return false;
        }
    }
};

void RefreshPath(long long int & path_length, long long int & path_count,
                 const long long int start_index, const long long int finish_index) {
    if (finish_index <= start_index) {
        return;
    }
    if (path_length < finish_index - start_index) {
        path_length = finish_index - start_index;
        path_count = 0;
    }
    if (path_length == finish_index - start_index) {
        ++path_count;
    }
}

std::tuple<long long int, long long int> DoTest() {
    long long int s;
    std::cin >> s;
    PointStorage point_storage;
    std::vector<Point> points;
    for (long long int i = 0; i < s; ++i) {
        long long int d,a,b;
        std::cin >> d >> a >> b;
        long long int x = d + a;
        long long int y = d - b;
        points.push_back({x, y});
    }
    long long int path_length = 0;
    long long int path_count = 0;
    long long int first_index = 0;
    long long int second_index = 0;
    while (first_index < s) {
        while (second_index < s && point_storage.IsCoveredByTwoSegments()) {
            point_storage.AddPoint(points[second_index]);
            ++second_index;
        }
        if (point_storage.IsCoveredByTwoSegments()) {
            // second_index == s
            RefreshPath(path_length, path_count, first_index, second_index);
            break;
        } else {
            RefreshPath(path_length, path_count, first_index, second_index - 1);
        }
        while (first_index < s && !point_storage.IsCoveredByTwoSegments()) {
            point_storage.RemovePoint(points[first_index]);
            ++first_index;
        }
    }
    return std::make_tuple(path_length, path_count);
}

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        long long int path_length;
        long long int path_count;
        std::tie(path_length, path_count) = DoTest();
        std::cout << "Case #" << i + 1 << ": " << path_length << " " << path_count << std::endl;
    }
    return 0;
}
