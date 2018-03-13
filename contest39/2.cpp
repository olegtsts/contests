#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    long long int n,m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    long long int sum_of_a = 0;
    for (long long int i = 0; i < n; ++i) {
        std::cin >> a[i];
        sum_of_a += a[i];
    }
    long long int max_number = *std::max_element(a.begin(), a.end());
    long long int first_position, last_position;
    first_position = -1;
    long long int sum_of_b = 0;
    for (long long int i = 0; i < n; ++i) {
        if (a[i] == max_number) {
            if (first_position == -1) {
                first_position = i;
            }
            last_position = i;
        }
    }
    std::vector<int> b(m);
    for (long long int i = 0; i < m; ++i) {
        std::cin >> b[i];
        sum_of_b += b[i];
    }
    long long int max_number_position = std::max_element(b.begin(), b.end()) - b.begin();
    if (first_position == last_position) {
        std::cout << (max_number * (m - 1) + sum_of_a) * 1000000000ll + sum_of_b + first_position * b[0] + (n - 1 - first_position) * b.back();
    } else {
        std::cout << (max_number * (m - 1) + sum_of_a) * 1000000000ll + sum_of_b + first_position * b[0] + (last_position - first_position) * b[max_number_position] + (n - 1 - last_position) * b.back();
    }
    std::cout << std::endl;
    return 0;
}
