#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> shows(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> shows[i].first >> shows[i].second;
        ++shows[i].second;
    }
    std::sort(shows.begin(), shows.end());
    int first_max = 0;
    int second_max = 0;
    for (auto& show: shows) {
        if (first_max <= show.first) {
            first_max = show.second;
        } else if (second_max <= show.first) {
            second_max = show.second;
        } else {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    return 0;
}
