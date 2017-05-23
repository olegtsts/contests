#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct Event {
    long long int coordinate;
    long long int type;
    long long int index;

    Event(const long long int coordinate, const long long int type, const long long int index)
    : coordinate(coordinate)
    , type(type)
    , index(index)
    {}

    bool operator< (const Event& other) const {
        return (
            coordinate < other.coordinate
            || (coordinate == other.coordinate && type < other.type)
            || (coordinate == other.coordinate && type == other.type && index < other.index)
        );
    }
};

int main () {
    int n; int m;
    std::cin >> n >> m;
    std::vector<Event> events;
    for (size_t i = 0; i < n; ++i) {
        long long int coordinate;
        std::cin >> coordinate;
        events.push_back(Event(coordinate, 1, i));
    }

    for (size_t i = 0; i < m; ++i) {
        long long int a,b;
        std::cin >> a >> b;
        events.push_back(Event(a, 0, i));
        events.push_back(Event(b, 2, i));
    }

    std::sort(events.begin(), events.end());

    std::vector<std::unordered_set<long long int>> days_people(n);
    std::unordered_set<long long int> cur_people;

    for (auto it = events.begin(); it != events.end(); ++it) {
        if (it->type == 0) {
            cur_people.insert(it->index);
        } else if (it->type == 2) {
            cur_people.erase(it->index);
        } else {
            days_people[it->index] = cur_people;
//            int cur_count = 0;
//            for (auto it2 = cur_people.begin(); it2 != cur_people.end(); ++it2) {
//                if (++cur_count >= 3) {
//                    break;
//                } else {
//                    days_people[it->index].insert(*it2);
//                }
//            }
        }
    }

    long long prev_uniq_person = -1;
    long long prev_people_count = -1;
    for (long long int i = n - 1; i >= 0; --i) {
        if (prev_people_count == 1) {
            days_people[i].erase(prev_uniq_person);
        }
        prev_people_count = days_people[i].size();
        if (prev_people_count == 0) {
            std::cout << "NO" << std::endl;
            return 0;
        }
        prev_uniq_person = *(days_people[i].begin());
    }

    std::cout << "YES" << std::endl;
    long long int prev_person = -1;
    for (size_t i = 0; i < n; ++i) {
        long long int cur_person = -1;
        for (auto it = days_people[i].begin(); it != days_people[i].end(); ++it) {
            if (*it != prev_person) {
                cur_person = *it;
                break;
            }
        }
        std::cout << cur_person + 1;
        prev_person = cur_person;
        if (i + 1 < n) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}

