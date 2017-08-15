#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

int main() {
    int n, a, b;
    std::cin >> n >> a >> b;
    std::vector<std::pair<int, int>> stamps(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> stamps[i].first >> stamps[i].second;
    }
    int max_area = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            for (int transpose_first = 0; transpose_first < 2; ++transpose_first) {
                for (int transpose_second = 0; transpose_second < 2; ++transpose_second) {
                    int x1 = transpose_first ? stamps[i].first : stamps[i].second;
                    int y1 = transpose_first ? stamps[i].second : stamps[i].first;
                    int x2 = transpose_second ? stamps[j].first : stamps[j].second;
                    int y2 = transpose_second ? stamps[j].second : stamps[j].first;

                    if ((std::max(x1, x2) <= a && y1 + y2 <= b)
                        || (x1 + x2 <= a && std::max(y1, y2) <= b)
                    ) {
                        int cur_area = stamps[i].first * stamps[i].second + stamps[j].first * stamps[j].second;
                        if (max_area < cur_area) {
                            max_area = cur_area;
                        }
                    }
                }
            }
        }
    }
    std::cout << max_area << std::endl;
    return 0;
}
