#include <limits>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> max_visited_index(200001, std::numeric_limits<int>::min());
    int n;
    std::cin >> n;
    std::vector<size_t> rooms(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> rooms[i];
        auto& room = rooms[i];
        if (max_visited_index[room] < i) {
            max_visited_index[room] = i;
        }
    }
    int min_visited_index = std::numeric_limits<int>::max();
    size_t min_visited_room = 0;
    for (int i = 0; i < n; ++i) {
        auto& room = rooms[i];
        if (max_visited_index[room] < min_visited_index) {
            min_visited_index = max_visited_index[room];
            min_visited_room = room;
        }
    }
    std::cout << min_visited_room << std::endl;
    return 0;
}
