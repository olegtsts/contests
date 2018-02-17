#include <iostream>

void DoTest() {
    long long int n;
    std::cin >> n;
    if (n == 0) {
        std::cout << "1 1\n";
        return;
    }
    for (long long int i = 1; i * i <= n; ++i) {
        long long int first_multiplier = i;
        if (n % first_multiplier != 0) {
            continue;
        }
        long long int second_multiplier = n / first_multiplier;
        if ((first_multiplier + second_multiplier) % 2 != 0) {
            continue;
        }
        long long int n = (first_multiplier + second_multiplier) / 2;
        long long int n_over_m = (second_multiplier - first_multiplier) / 2;
        if (n_over_m == 0) {
            continue;
        }
        for (long long int possible_m = n / n_over_m; possible_m > 0 && n / possible_m <= n_over_m; --possible_m) {
            if (n / possible_m == n_over_m) {
                std::cout << n << " " << possible_m << std::endl;
                return;
            }
        }
    }
    std::cout << "-1\n";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        DoTest();
    }
    return 0;
}
