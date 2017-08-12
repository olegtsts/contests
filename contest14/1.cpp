#include <algorithm>
#include <iostream>

int main() {
    int n;
    int k;
    std::cin >> n >> k;
    int sum_candies = 0;
    int given_out_candies = 0;
    int days_exceeded = 0;
    for (int i = 0; i < n; ++i) {
        int candies;
        std::cin >> candies;
        sum_candies += candies;
        int give_out_candies = std::min(8, sum_candies);
        given_out_candies += give_out_candies;
        sum_candies -= give_out_candies;
        ++days_exceeded;
        if (given_out_candies >= k) {
            break;
        }
    }
    if (given_out_candies >= k) {
        std::cout << days_exceeded << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
    return 0;
}
