#include <iostream>
#include <vector>
#include <algorithm>

int GetMinOption(int number, int max_prime_divisor) {
    if (number > max_prime_divisor) {
        return number - max_prime_divisor + 1;
    } else {
        return number;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<char> prime (n+1, true);
    prime[0] = prime[1] = false;
    for (int i=2; i<=n; ++i) {
        if (prime[i]) {
            if (i * 1ll * i <= n) {
                for (int j=i*i; j<=n; j+=i) {
                    prime[j] = false;
                }
            }
        }
    }
    int max_prime_divisor = 1;
    for (int i = 2; i <=n; ++i) {
        if (n % i == 0 && prime[i]) {
            max_prime_divisor = i;
        }
    }
    int lower_option = GetMinOption(n, max_prime_divisor);
    int second_min_option = n;
    for (int i = 2; i <= n; ++i) {
        if (prime[i]) {
            int new_number = (lower_option + i - 1) / i * i;
            if (new_number != i && new_number >= lower_option && new_number <= n) {
                second_min_option = std::min(second_min_option, GetMinOption(new_number, i));
            }
        }
    }
    std::cout << second_min_option << std::endl;
    return 0;
}
