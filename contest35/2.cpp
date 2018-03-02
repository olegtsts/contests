#include <iostream>
#include <vector>

int main() {
    long long int p, y;
    std::cin >> p >> y;
    std::vector<char> is_prime (32001, true);
    is_prime[0] = is_prime[1] = false;

    std::vector<int> primes;

    for (int i=2; i<=32000; ++i) {
        if (is_prime[i]) {
            if (i <= p) {
                primes.push_back(i);
            }
            if (i * 1ll * i <= 32000) {
                for (int j=i*i; j<=32000; j+=i) {
                    is_prime[j] = false;
                }
            }
        }
    }

    while (y > p) {
        bool is_number_ok = true;
        for (auto& prime: primes) {
            if (y % prime == 0) {
                is_number_ok = false;
                break;
            }
        }
        if (is_number_ok) {
            std::cout << y << std::endl;
            return 0;
        }
        --y;
    }
    std::cout << "-1\n" << std::endl;
    return 0;
}
