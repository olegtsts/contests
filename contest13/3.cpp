#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>

struct Ride {
    int l;
    int r;
    long long int cost;
};

class Segments {
private:
   void count_prefix_min(std::map<int, long long int>& point_cost) {
        long long int prev_value = LLONG_MAX;
        for (auto& pair: point_cost) {
            pair.second = std::min(pair.second, prev_value);
            prev_value = pair.second;
        }
    }
    long long int get_min_before(std::map<int, long long int>& point_cost, const int value) {
        auto it = point_cost.lower_bound(value);
        if (it != point_cost.begin()) {
            --it;
            return it->second;
        } else {
            return LLONG_MAX;
        }
    }
    void add_min(std::map<int, long long int>& point_cost, const int key, const long long int value) {
        long long int old_value = LLONG_MAX;
        if (point_cost.count(key) > 0) {
            old_value = point_cost[key];
        }
        point_cost[key] = std::min(value, old_value);
    }
public:
    void add_segment_with_cost(const int l, const int r, const long long int cost) {
        add_min(left_point_cost, -l, cost);
        add_min(right_point_cost, r, cost);
        rides.push_back(Ride{l, r, cost});
    }

    void prepare() {
        count_prefix_min(left_point_cost);
        count_prefix_min(right_point_cost);
    }
    long long int get_min_not_in_segment(const int l, const int r) {
        return std::min(get_min_before(right_point_cost, l), get_min_before(left_point_cost, -r));
    }

    template <typename TFunc>
    void for_each(TFunc function) {
        for (auto& ride : rides) {
            function(ride);
        }
    }
    size_t size() {
        return rides.size();
    }
private:
    std::map<int, long long int> left_point_cost;
    std::map<int, long long int> right_point_cost;
    std::vector<Ride> rides;
};

int main() {
    int n,x;
    std::cin >> n >> x;
    std::vector<Segments> length_index(200001);
    for (int i = 0; i < n; ++i) {
        int l,r;
        long long int cost;
        std::cin >> l >> r >> cost;
        length_index[r - l + 1].add_segment_with_cost(l, r, cost);
    }
    for (auto& segments: length_index) {
        segments.prepare();
    }
    long long int min_cost = LLONG_MAX;
    for (size_t length = 0; static_cast<int>(length) <= x; ++length) {
        if (length_index[length].size() > 0 && x - length >= 0 && length_index[x - length].size() > 0) {
            auto& segments = length_index[length];
            auto& another_segments = length_index[x - length];
            segments.for_each([&another_segments, &min_cost] (const Ride& ride) {
                auto min_another_cost = another_segments.get_min_not_in_segment(ride.l, ride.r);
                if (min_another_cost < LLONG_MAX && min_another_cost + ride.cost < min_cost) {
                    min_cost = min_another_cost + ride.cost;
                }
            });
        }
    }
    std::cout << (min_cost == LLONG_MAX ? -1 : min_cost) << std::endl;
    return 0;
}
