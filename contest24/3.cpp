#pragma GCC target ("avx,tune=native")
#pragma GCC optimize ("O3")
#include <vector>
#include <iostream>
#include <algorithm>

long long int MODULO = 1000000007;

int main() {
    std::ios::sync_with_stdio(false);
    std::vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
    std::vector<long long int> counts(524288, 0);
    std::vector<long long int> new_counts(524288, 0);
    counts[0] = 1;
    int n;
    std::cin >> n;
    std::vector<long long int> masks(71, 0);
    for (size_t number = 1; number <= 70; ++number) {
        size_t a = number;
        for (size_t prime_index = 0; prime_index < primes.size(); ++prime_index) {
            auto prime = primes[prime_index];
            size_t count_of_prime = 0;
            while (a % prime == 0) {
                a /= prime;
                ++count_of_prime;
            }
            if (count_of_prime % 2 == 1) {
                masks[number] ^= (1 << prime_index);
            }
            if (a == 1) {
                break;
            }
        }
    }

    std::vector<long long int> numbers(n, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    for (int i = 0; i < n; ++i) {
        long long int total_xor = masks[numbers[i]];
        for (size_t i = 0; i < 524288; ++i) {
            new_counts[i] = counts[i] + counts[i ^ total_xor];
            new_counts[i] %= MODULO;
        }
        std::swap(counts, new_counts);
    }
    std::cout << (counts[0] + MODULO - 1) % MODULO << std::endl;
    return 0;
}
