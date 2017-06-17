#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

enum EventType {RECIPE_OPEN, QUERY_OPEN, QUERY_CLOSE, RECIPE_CLOSE};

class Event {
public:
    Event()
    {}
    Event(const long long int coord, const EventType type, const int index)
    : coord(coord)
    , type(type)
    , index(index)
    {}

    bool operator<(const Event& other) const {
        return coord < other.coord
            || (coord == other.coord && type < other.type)
            || (coord == other.coord && type == other.type && index < other.index);
    }
long long int coord;
EventType type;
int index;
};

int main() {
    int k,n,q;
    std::cin >> n >> k >> q;
    std::vector<Event> events(2 * n + 2 * q);
    std::vector<std::pair<long long int, long long int> > queries(q);
    for (size_t i = 0; i < n; ++i) {
        long long int l, r;
        std::cin >> l >> r;
        events[2 * i] = Event(l, RECIPE_OPEN, i);
        events[2 * i + 1] = Event(r + 1, RECIPE_CLOSE, i);
    }
    for (size_t i = 0; i < q; ++i) {
        long long int a,b;
        std::cin >> a >> b;
        events[2 * n + 2 * i] = Event(a, QUERY_OPEN, i);
        events[2 * n + 2 * i + 1] = Event(b + 1, QUERY_CLOSE, i);
        queries[i] = std::make_pair(a, b);
    }
    std::sort(events.begin(), events.end());
    int current_recipies = 0;
    std::vector<int> counts(q, 0);
    long long int last_seen = events[0].coord;
    std::unordered_set<int> active_query_indices;
    for (auto& event: events) {
        if (current_recipies >= k) {
            for (auto& index: active_query_indices) {
                counts[index] += event.coord - std::max(last_seen, queries[index].first);
            }
        }
        if (event.type == RECIPE_OPEN) {
            ++current_recipies;
        } else if (event.type == QUERY_OPEN) {
            active_query_indices.insert(event.index);
        } else if (event.type == RECIPE_CLOSE) {
            --current_recipies;
        } else if (event.type == QUERY_CLOSE) {
            active_query_indices.erase(event.index);
        }
        last_seen = event.coord;
    }
    for (auto& count: counts) {
        std::cout << count << std::endl;
    }
    return 0;
}
