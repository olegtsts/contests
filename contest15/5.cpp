#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>

long long my_gcd(long long int a, long long int b) {
    while (b > 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    long long int a,b;
    std::cin >> a >> b;
    std::set<long long int> a_primes;
    long long int a_copy = a;
    for (int i = 2; i <= sqrt(static_cast<double>(a)); ++i) {
        while (a_copy % i == 0) {
            a_primes.insert(i);
            a_copy /= i;
        }
        if (a_copy == 1) {
            break;
        }
    }
    if (a_copy > 1) {
        a_primes.insert(a_copy);
    }

    long long int result = 0;
    while (a > 1 && b > 0) {
        long long int gcd_res = my_gcd(a, b);
        if (gcd_res > 1) {
            a /= gcd_res;
            b /= gcd_res;
            std::set<long long int> new_a_primes;
            for (auto& prime: a_primes) {
                if (a % prime == 0) {
                    new_a_primes.insert(prime);
                }
            }
            a_primes = std::move(new_a_primes);
        } else {
            long long int min_shift = LLONG_MAX;
            for (auto& prime: a_primes) {
                long long int cur_shift = b % prime;
                if (cur_shift < min_shift) {
                    min_shift = cur_shift;
                }
            }
            b -= min_shift;
            result += min_shift;
        }
    }
    result += b;
    std::cout << result << std::endl;
    return 0;
}
