#include <iostream>
#include <vector>

const long long int MODULO = 1000000007;

int main() {
    long long int t;
    int l,r;
    std::cin >> t >> l >> r;
    std::vector<int> primes;
    std::vector<int> lp(r + 1, 0);
    for (int i = 2; i <= r; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (auto& prime: primes) {
            if (prime <= lp[i] && i * prime <= r) {
                lp[i * prime] = prime;
            } else {
                break;
            }
        }
    }
    std::vector<long long int> f(r + 1, 0);
    f[1] = 0;
    for (int i = 2; i <= r; ++i) {
        long long int prime = lp[i];
        long long int addon;
        if (prime == 2) {
            addon = 1;
        } else {
            addon = ((prime - 1) / 2 * prime) % MODULO;
        }
        long long int buckets_count = i / prime;
        f[i] = f[buckets_count];
        f[i] += (addon * buckets_count) % MODULO;
        f[i] %= MODULO;
    }
    long long int result = 0;
    for (int i = r; i >= l; --i) {
        result += f[i];
        result %= MODULO;
        if (i > l) {
            result *= t;
            result %= MODULO;
        }
    }
    std::cout << result << std::endl;
    return 0;
}
