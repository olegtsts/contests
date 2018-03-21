#include <iostream>
#include <vector>

int main() {
    int n,m;
    std::cin >> n >> m;
    std::vector<int> x(n);
    std::vector<int> y(m);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> y[i];
    }
    int first_sum = 0;
    int second_sum = 0;
    int first_index = 0;
    int second_index = 0;
    int files_count = 0;
    while (first_index < n || second_index < m) {
        bool take_first;
        if (second_index == m) {
            take_first = true;
        } else if (first_index == n) {
            take_first = false;
        } else {
            take_first = (first_sum < second_sum);
        }
        if (take_first) {
            first_sum += x[first_index++];
        } else {
            second_sum += y[second_index++];
        }
        if (first_sum == second_sum) {
            ++files_count;
        }
    }
    std::cout << files_count << std::endl;
    return 0;
}
