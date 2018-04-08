#include <iostream>

int main() {
    long long int n;
    std::cin >> n;
    int total_score = 0;

    while (n > 0) {
        bool reached_one_point = false;
        for (int i = 0; i < 31; ++i) {
            long long int m = (1ll << i);
            long long int r = n % m;
            long long int new_n = n / m;
            if (r > m / 2) {
                ++total_score;
                reached_one_point = true;
                n = new_n;
                break;
            }
        }
        if (!reached_one_point) {
            break;
        }
    }
    std::cout << total_score << std::endl;
}
