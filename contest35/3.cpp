#include <iostream>

int main() {
    long long int k,d,t;
    std::cin >> k >> d >> t;
    long long int x = (d + k - 1) / d;
    long long int remain = x * d - k;
    long long int periodic_time = 2 * k + remain;
    long long int periodic_segments = 2 * t / periodic_time;
    long long int after_periodic = 2 * t - periodic_time * periodic_segments;
    long long int result = periodic_segments * (k + remain);
    if (after_periodic > 2 * k) {
        result += after_periodic - 2 * k;
        after_periodic = 2 * k;
    }
    result += after_periodic / 2;
    std::cout << result;
    if (after_periodic % 2 != 0) {
        std::cout << ".5";
    }
    std::cout << std::endl;
    return 0;
}
