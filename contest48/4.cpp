#include <iostream>
#include <vector>

void ApplyShift(
    long long int& x,
    const long long int power_of_two,
    const long long int shift
) {
    x -= power_of_two;
    x += shift;
    x %= power_of_two;
    x += power_of_two;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::vector<long long int> shifts(60, 0);
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;
        if (type == 1) {
            long long int x, k;
            std::cin >> x >> k;
            long long int power_of_two = 1;
            int power_value = 0;
            while (power_of_two <= x) {
                power_of_two <<= 1;
                ++power_value;
            }
            power_of_two >>= 1;
            --power_value;
            k %= power_of_two;
            k += power_of_two;
            k %= power_of_two;
            shifts[power_value] += k;
            shifts[power_value] %= power_of_two;
        } else if (type == 2) {
            long long int x, k;
            std::cin >> x >> k;
            long long int power_of_two = 1;
            int power_value = 0;
            while (power_of_two <= x) {
                power_of_two <<= 1;
                ++power_value;
            }
            power_of_two >>= 1;
            --power_value;
            for (int value = power_value; value < 60; ++value) {
                k %= power_of_two;
                k += power_of_two;
                k %= power_of_two;
                shifts[value] += k;
                shifts[value] %= power_of_two;
                power_of_two <<= 1;
                k <<= 1;
            }
        } else {
            long long int x;
            std::cin >> x;
            long long int power_of_two = 1;
            int power_value = 0;
            while (power_of_two <= x) {
                power_of_two <<= 1;
                ++power_value;
            }
            power_of_two >>= 1;
            --power_value;
            ApplyShift(x, power_of_two, shifts[power_value]);
            while (x > 0) {
                long long int new_x = x / 2;
                ApplyShift(x, power_of_two, power_of_two - shifts[power_value]);
                --power_value;
                power_of_two >>= 1;
                std::cout << x << " ";
                x = new_x;
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
