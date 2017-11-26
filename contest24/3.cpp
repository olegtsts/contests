#include <vector>
#include <iostream>

long long int MODULO = 1000000007;

int main() {
    std::ios::sync_with_stdio(false);
    std::vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
    std::vector<long long int> counts(524288, 0);
    counts[0] = 1;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int a = 0;
        std::cin >> a;
        int total_xor = 0;
        for (size_t prime_index = 0; prime_index < primes.size(); ++prime_index) {
            auto prime = primes[prime_index];
            int count_of_prime = 0;
            while (a % prime == 0) {
                a /= prime;
                ++count_of_prime;
            }
            if (count_of_prime % 2 == 1) {
                total_xor ^= (1 << prime_index);
            }
            if (a == 1) {
                break;
            }
        }
        for (size_t i = 0; i < 524288; ++i) {
            if (i > (i ^ total_xor)) {
                counts[i] += counts[i ^ total_xor];
                counts[i] %= MODULO;
            }
        }
    }
    std::cout << (counts[0] + MODULO - 1) % MODULO << std::endl;
    return 0;
}
