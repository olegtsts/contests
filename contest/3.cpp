#include <iostream>
#include <vector>
#include <algorithm>

void add_person(std::vector<long long int>& people, const size_t offset, const size_t person) {
    long long int last_minus_one_index = -1;
    bool is_there_person_already = false;
    for (size_t i = offset; i < 4 + offset; ++i) {
        if (people[i] == -1) {
            last_minus_one_index = i;
        }
        if (people[i] == person) {
            is_there_person_already = true;
        }
    }
    if (!is_there_person_already && last_minus_one_index != -1) {
        people[last_minus_one_index] = person;
    }
}

bool delete_person(std::vector<long long int>& people, const size_t offset, const size_t person) {
    long long int person_index = -1;
    bool was_there_deletion = false;
    for (size_t i = offset; i < 4 + offset; ++i) {
        if (people[i] == person) {
            person_index = i;
        }
    }
    if (person_index != -1) {
        people[person_index] = -1;
        was_there_deletion = true;
    }
    return was_there_deletion;
}

int get_people_count(std::vector<long long int>& people, const size_t offset) {
    int count_of_people = 0;
    for (size_t i = offset; i < 4 + offset; ++i) {
        if (people[i] != -1) {
            ++count_of_people;
        }
    }
    return count_of_people;
}

long long int get_any_person(std::vector<long long int>& people, const size_t offset) {
    for (size_t i = offset; i < 4 + offset; ++i) {
        if (people[i] != -1) {
            return people[i];
        }
    }
    return -1;
}


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
        return (coordinate < other.coordinate || (coordinate == other.coordinate && type < other.type));
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

    std::vector<long long int> days_people(n * 4, -1);
    std::vector<long long int> cur_people(4, -1);

    for (auto it = events.begin(); it != events.end(); ++it) {
        if (it->type == 0) {
            add_person(cur_people, 0, it->index);
        } else if (it->type == 2) {
            delete_person(cur_people, 0, it->index);
        } else {
            for (size_t i = 0; i < 4; ++i) {
                if (cur_people[i] != -1) {
                    add_person(days_people, 4 * it->index, cur_people[i]);
                }
            }
        }
    }
    long long prev_uniq_person = -1;
    long long prev_people_count = -1;
    for (long long int i = n - 1; i >= 0; --i) {
        if (prev_people_count == 1) {
            delete_person(days_people, 4 * i, prev_uniq_person);
        }
        prev_people_count = get_people_count(days_people, 4 * i);
        prev_uniq_person = get_any_person(days_people, 4 * i);
        if (prev_people_count == 0) {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }

    std::cout << "YES" << std::endl;
    long long int prev_person = -1;
    for (size_t i = 0; i < n; ++i) {
        long long int cur_person = -1;
        for (size_t j = 0; j < 4; ++j) {
            long long int person = days_people[4 * i + j];
            if (person != -1 && person != prev_person) {
                cur_person = person;
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

