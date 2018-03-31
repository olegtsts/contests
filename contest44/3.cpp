#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <iomanip>

struct Horse {
    long long int x;
    long long int v;

    bool operator<(const Horse& other) const {
        return std::forward_as_tuple(other.v, other.x) < std::forward_as_tuple(v, x);
    }
};

bool WillMeetBefore(const Horse& first_horse, const Horse& second_horse, const long long int d) {
    if ((first_horse.x - second_horse.x) * (first_horse.v - second_horse.v) > 0) {
        return false;
    } else {
        return second_horse.v * first_horse.x - first_horse.v * second_horse.x <= d * second_horse.v - d * first_horse.v;
    }
}

long double DoTest() {
    long long int d;
    int n;
    std::cin >> d >> n;
    std::vector<Horse> horses(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> horses[i].x >> horses[i].v;
    }
    std::sort(horses.begin(), horses.end());
    std::vector<Horse> filtered_horses;
    for (int i = 0; i < n; ++i) {
        bool does_horse_intersect = false;
        for (int j = i + 1; j < n; ++j) {
            if (WillMeetBefore(horses[i], horses[j], d)) {
                does_horse_intersect = false;
                break;
            }
        }
        if (!does_horse_intersect) {
            filtered_horses.push_back(horses[i]);
        }
    }
    long double target_speed = std::numeric_limits<long double>::max();
    for (auto horse: filtered_horses) {
        long double new_speed = static_cast<long double>(d) / (d - horse.x) * horse.v;
        target_speed = std::min(target_speed, new_speed);
    }
    return target_speed;
}

int main() {
    int t;
    std::cin >> t;
    std::cout << std::setprecision(10);
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ": " << DoTest() << std::endl;
    }
    return 0;
}
