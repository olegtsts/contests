#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <limits>


long long int GetBestStairsOfElevator(
    const std::vector<long long int>& el_positions,
    const long long int y1, const long long int y2
) {
    std::vector<long long int> options;
    auto it = std::lower_bound(el_positions.begin(), el_positions.end(), y1);
    if (it != el_positions.end()) {
        options.push_back(*it);
    }
    it = std::upper_bound(el_positions.begin(), el_positions.end(), y2);
    if (it != el_positions.begin()) {
        --it;
        options.push_back(*it);
    }
    long long int best_distance = std::numeric_limits<long long int>::max();
    for (auto option: options) {
        long long int legnth = abs(option - y1) + abs(option - y2);
        if (legnth < best_distance) {
            best_distance = legnth;
        }
    }
    return best_distance;
}

int main() {
    long long int n,m,c_l, c_e, v;
    std::cin >> n >> m >> c_l >> c_e >> v;
    std::vector<long long int> stairs(c_l);
    for (long long int i = 0; i < c_l; ++i) {
        std::cin >> stairs[i];
    }
    std::vector<long long int> elevators(c_e);
    for (long long int i = 0; i < c_e; ++i) {
        std::cin >> elevators[i];
    }
    long long int q;
    std::cin >> q;
    for (long long int i = 0; i < q; ++i) {
        long long int x1,y1,x2,y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        if (y1 > y2) {
            std::swap(y1, y2);
        }
        long long int floors = x2 - x1;
        long long int best_result = std::numeric_limits<long long int>::max();
        if (floors == 0) {
            best_result = std::min(best_result, y2 - y1);
        }
        if (stairs.size() > 0) {
            long long int stairs_result = floors + GetBestStairsOfElevator(stairs, y1, y2);
            best_result = std::min(best_result, stairs_result);
        }
        if (elevators.size() > 0) {
            long long int elevator_result = (x2 - x1 + v - 1) / v + GetBestStairsOfElevator(elevators, y1, y2);
            best_result = std::min(best_result, elevator_result);
        }
        std::cout << best_result << std::endl;
    }
    return 0;
}
