#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    int n,p;
    std::cin >> n >> p;
    std::vector<int> a(n);
    int total_points_sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        total_points_sum += a[i];
        total_points_sum %= p;
    }
    int first_points = a[0] % p;
    int second_points = (((total_points_sum - a[0]) % p) + p) % p;
    int max_points = first_points + second_points;
    for (int i = 1; i + 1 < n; ++i) {
        first_points += a[i];
        second_points -= a[i];
        first_points %= p;
        second_points %= p;
        first_points += p;
        second_points += p;
        first_points %= p;
        second_points %= p;
        max_points = std::max(max_points, first_points + second_points);
    }
    std::cout << max_points << std::endl;
    return 0;
}
