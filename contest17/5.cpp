#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

bool IsThereNotCoveredInSegment(
    std::map<long long int,int>& centers,
    const long long int radius,
    const long long int max_coord
) {
    if (centers.size() == 0) {
        return true;
    }
    auto it = centers.begin();
    if (it->first > radius) {
        return true;
    }
    it = centers.end();
    --it;
    if (max_coord > it->first + radius + 1) {
        return true;
    }
    it = centers.begin();
    while (it != centers.end()) {
        auto next_it = it;
        ++next_it;
        if (next_it != centers.end()) {
            if (next_it->first - it->first > 2 * radius + 1) {
                return true;
            }
        }
        it = next_it;
    }
    return false;
}

struct Event {
    enum EventType {ADD, REMOVE};
    long long int y;
    EventType type;
};

void UpdateMap(std::map<long long int, std::vector<Event>>& events,
               const long long int x,
               const long long int y,
               const Event::EventType type) {
    if (events.count(x) == 0) {
        events.insert(std::make_pair(x, std::vector<Event>{}));
    }
    events[x].push_back(Event{y, type});
}

long long int GetMinNotFilledCoord(const std::vector<long long int>& points,
                                   const size_t coord_shift,
                                   const long long int radius,
                                   const long long int x_max_coord,
                                   const long long int y_max_coord,
                                   const int k) {
    std::map<long long int, std::vector<Event>> events;
    std::map<long long int, int> line_points;
    const size_t another_coord = 1 - coord_shift;
    events.insert(std::make_pair(0, std::vector<Event>{}));
    events.insert(std::make_pair(x_max_coord - 1, std::vector<Event>{}));
    for (int i = 0; i < k; ++i) {
        UpdateMap(events, points[2 * i + coord_shift] - radius, points[2 * i + another_coord], Event::EventType::ADD);
        UpdateMap(events, points[2 * i + coord_shift] + radius + 1, points[2 * i + another_coord], Event::EventType::REMOVE);
    }
    for (auto& event_pair: events) {
        long long int x = event_pair.first;
        for (auto& event: event_pair.second) {
            if (event.type == Event::EventType::ADD) {
                if (line_points.count(event.y) == 0) {
                    line_points[event.y] = 0;
                }
                ++line_points[event.y];
            } else {
                --line_points[event.y];
                if (line_points[event.y] == 0) {
                    line_points.erase(event.y);
                }
            }
        }
        if (x >= 0 && x < x_max_coord && IsThereNotCoveredInSegment(line_points, radius, y_max_coord)) {
            return x;
        }
    }
    return x_max_coord;
}

bool CanBeCoveredWithOneOdd(const std::vector<long long int>& points,
                  const long long int radius,
                  const long long int n,
                  const long long int m,
                  const int k) {
    auto x = GetMinNotFilledCoord(points, 0, radius, n, m, k);
    if (x >= n) {
        return true;
    }
    auto y = GetMinNotFilledCoord(points, 1, radius, m, n, k);
    if (y >= m) {
        return true;
    }
    std::vector<long long int> new_points(points);
    new_points.push_back(std::min(x + radius, n - 1));
    new_points.push_back(std::min(y + radius, m - 1));
    auto new_x = GetMinNotFilledCoord(new_points, 0, radius, n, m, k + 1);
    return new_x >= n;
}

long long int GetMinRadius(std::vector<long long int>& points,
                           const long long int n,
                           const long long int m,
                           const int k) {
    long long int left = 0;
    long long int right = 1000000001;
    if (k == m * n || k + 1 == m * n) {
        return 0;
    }
    while (right > left + 1) {
        long long int middle = (right + left) / 2;
        if (CanBeCoveredWithOneOdd(points, middle, n, m, k)) {
            right = middle;
        } else {
            left = middle;
        }
    }
    return left + 1;
}

int main() {
    long long int n,m;
    int k;
    std::cin >> n >> m >> k;
    std::vector<long long int> points(2 * k);
    for (int i = 0; i < k; ++i) {
        std::cin >> points[2 * i] >> points[2 * i + 1];
        --points[2 * i];
        --points[2 * i + 1];
    }
    std::cout << GetMinRadius(points, n, m, k) << std::endl;
    return 0;
}
