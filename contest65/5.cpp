#include <iostream>
#include <vector>
#include <cstdio>

int A(int a) {
    std::cout << "A " << a << std::endl;
    fflush(stdout);
    int n;
    std::cin >> n;
    return n;
}

int B(int a) {
    std::cout << "B " << a << std::endl;
    fflush(stdout);
    int n;
    std::cin >> n;
    return n;
}

void C(int a) {
    std::cout << "C " << a << std::endl;
    fflush(stdout);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<char> prime (n+1, true);
    prime[0] = prime[1] = false;
    for (int i=2; i<=n; ++i)
        if (prime[i])
            if (i * 1ll * i <= n)
                for (int j=i*i; j<=n; j+=i)
                    prime[j] = false;

    std::vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (prime[i]) {
            primes.push_back(i);
        }
    }
    size_t prime_index = 0;
    while (prime_index < primes.size() && primes[prime_index] < 330) {
        B(primes[prime_index]);
        ++prime_index;
    }
    prime_index = 0;
    while (prime_index < primes.size() && primes[prime_index] < 330) {
        if (A(primes[prime_index]) == 1) {
            int base_prime = primes[prime_index];
            int result_number = base_prime;
            while (prime_index < primes.size()) {
                int number_to_check = primes[prime_index] * base_prime;
                while (number_to_check <= n && A(number_to_check) > 0) {
                    result_number *= primes[prime_index];
                    if (number_to_check > (n + primes[prime_index] - 1) / primes[prime_index]) {
                        break;
                    }
                    number_to_check *= primes[prime_index];
                }
                ++prime_index;
            }
            C(result_number);
            return 0;
        }
        ++prime_index;
    }
    bool found_divisor = false;
    int least_prime_index = prime_index;
    while (prime_index < primes.size()) {
        if (prime_index % 100 == 0) {
            if (A(1) - 1 == static_cast<int>(primes.size() - prime_index)) {
                least_prime_index = prime_index;
            } else {
                found_divisor = true;
                break;
            }
        }
        B(primes[prime_index]);
        ++prime_index;
    }

    if (A(1) - 1 == static_cast<int>(primes.size() - prime_index)) {
        least_prime_index = prime_index;
    } else {
        found_divisor = true;
    }
    if (found_divisor) {
        prime_index = least_prime_index;
        for (int i = 0; i < 100; ++i) {
            if (A(primes[prime_index]) == 1) {
                C(primes[prime_index]);
                return 0;
            }
            ++prime_index;
        }
    } else {
        C(1);
        return 0;
    }
    return 0;
}
