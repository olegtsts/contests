#include <vector>
#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    int n = 2000000;
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
//    std::cout << primes.size() << std::endl;
    std::vector<bool> primes_used(primes.size(), false);
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    int number_to_change_index = -1;
    for (int i = 0; i < n; ++i) {
        int number = numbers[i];
        int prime_index = 0;
        bool finish = false;
        std::vector<int> new_used_primes;
        while (number > 1) {
            if (number % primes[prime_index] == 0) {
                if (primes_used[prime_index]) {
                    finish = true;
                    number_to_change_index = i;
                    break;
                } else {
                    while (number % primes[prime_index] == 0) {
                        number /= primes[prime_index];
                    }
                    new_used_primes.push_back(prime_index);
                    ++prime_index;
                }
            } else {
                ++prime_index;
            }
        }
        if (finish) {
            break;
        }
        for (auto prime_index: new_used_primes) {
            primes_used[prime_index] = true;
        }
    }
    std::vector<int> used_primes;
    std::deque<int> not_used_primes;
    for (size_t prime_index = 0; prime_index < primes.size(); ++prime_index) {
        if (primes_used[prime_index]) {
            used_primes.push_back(primes[prime_index]);
        }
    }
    if (number_to_change_index > -1) {
        while (true) {
            ++numbers[number_to_change_index];
            bool is_divisible_by_any = false;
            for (auto prime: used_primes) {
                if (numbers[number_to_change_index] % prime == 0) {
                    is_divisible_by_any = true;
                    break;
                }
            }
            if (!is_divisible_by_any) {
                break;
            }
        }
        int number = numbers[number_to_change_index];
        int prime_index = 0;
        while (number > 1) {
            if (number % primes[prime_index] == 0) {
                while (number % primes[prime_index] == 0) {
                    number /= primes[prime_index];
                }
                if (!primes_used[prime_index]) {
                    used_primes.push_back(prime[prime_index]);
                    primes_used[prime_index] = true;
                }
            }
            ++prime_index;
        }
        std::deque<int> not_used_primes;
        for (size_t prime_index = 0; prime_index < primes.size(); ++prime_index) {
            if (!primes_used[prime_index]) {
                not_used_primes.push_back(primes[prime_index]);
            }
        }
        for (int i = number_to_change_index + 1; i < n; ++i) {
            numbers[i] = not_used_primes.front();
            not_used_primes.pop_front();
        }
    }
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i];
        if (i + 1 < numbers.size()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
