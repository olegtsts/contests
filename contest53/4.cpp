#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    int l;
    int n;
    std::cin >> n >> l;
    std::vector<long long int> stones_limits(n, 0);
    long long int max_total_frogs = 0;
    for (int i = 0; i + 1 < n; ++i) {
        std::cin >> stones_limits[i];
        max_total_frogs += stones_limits[i];
    }
    int min_frogs = 0;
    int max_frogs = max_total_frogs + 1;
    stones_limits[n - 1] = max_frogs;
    while (max_frogs - min_frogs >= 2) {
        int mid_frogs = (min_frogs + max_frogs) / 2;
        std::vector<long long int> frogs_in_position(n + 2, 0);
        frogs_in_position[0] = mid_frogs;
        bool is_possible = true;
        int from_position = 0;
        int to_position = 1;
        while (to_position < n + 1) {
            while (stones_limits[to_position - 1] == frogs_in_position[to_position]) {
                ++to_position;
            }
            if (to_position - from_position > l) {
                is_possible = false;
                break;
            }
            long long int how_much_needed = stones_limits[to_position - 1] - frogs_in_position[to_position];
            long long int how_much_have = frogs_in_position[from_position];
            long long int how_much_to_transfer = std::min(how_much_needed, how_much_have);
            frogs_in_position[from_position] -= how_much_to_transfer;
            frogs_in_position[to_position] += how_much_to_transfer;
            while (!frogs_in_position[from_position]) {
                ++from_position;
                if (to_position == from_position) {
                    ++to_position;
                }
            }
        }
        if (is_possible) {
            min_frogs = mid_frogs;
        } else {
            max_frogs = mid_frogs;
        }
    }
    std::cout << min_frogs << std::endl;
    return 0;
}
