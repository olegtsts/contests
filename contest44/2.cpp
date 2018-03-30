#include <iostream>
#include <tuple>
#include <set>

struct Group {
    char letter;
    int people;

    bool operator<(const Group& other) const {
        return std::forward_as_tuple(people, letter) > std::forward_as_tuple(other.people, other.letter);
    }
};

void DoTest(const int number_of_test) {
    std::set<Group> groups;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int people;
        std::cin >> people;
        groups.insert({char('A' + i), people});
    }
    std::cout << "Case #" << number_of_test + 1 << ":";
    if (groups.size() > 2) {
        while (groups.begin()->people > 1) {
            auto group = *groups.begin();
            std::cout << " " << group.letter;
            groups.erase(group);
            groups.insert({group.letter, group.people - 1});
        }
        while (groups.size() > 2) {
            auto group = *groups.begin();
            groups.erase(group);
            std::cout << " " << group.letter;
        }
    }
    if (groups.size() == 2) {
        auto first_group = *groups.begin();
        groups.erase(first_group);
        auto second_group = *groups.begin();
        for (int i = 0; i < first_group.people; ++i) {
            std::cout << " " << first_group.letter << second_group.letter;
        }
    }
    std::cout << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        DoTest(i);
    }
    return 0;
}
