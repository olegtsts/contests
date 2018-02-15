#include <iostream>
#include <vector>

int main() {
//    std::ios::sync_with_stdio(false);
    int n,k;
    std::cin >> n >> k;

    std::vector<bool> prime (n+1, true);
    std::vector<int> divisible_by(n + 1, 1);
    prime[0] = prime[1] = false;
    for (int i=2; i<=n; ++i)
        if (prime[i]) {
            divisible_by[i] = i;
            if (i * 1ll * i <= n)
                for (int j=i*i; j<=n; j+=i) {
                    divisible_by[j] = i;
                    prime[j] = false;
                }
        }

    std::vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (prime[i]) {
            primes.push_back(i);
        }
    }

    std::vector<int> divisors_count(n + 1, 0);
    divisors_count[1] = 1;
    for (int i = 2; i <= n; ++i) {
        int prime = divisible_by[i];
        if (i % prime == 0) {
            int count_of_prime = 0;
            int number = i;
            while (number % prime == 0) {
                ++count_of_prime;
                number /= prime;
            }
            divisors_count[i] = divisors_count[number] * (count_of_prime + 1);
        }
    }

    int current_pairs_count = 0;
    int max_used = 1;
    for (; max_used <= n; ++max_used) {
        current_pairs_count += divisors_count[max_used] - 1;
        if (current_pairs_count >= k) {
            break;
        }
    }
    if (current_pairs_count < k) {
        std::cout << "No\n";
        return 0;
    }
    std::cout << "Yes\n";
    std::vector<int> elements_to_omit;
    for (auto& prime: primes) {
        if (current_pairs_count == k) {
            break;
        }
        if (max_used < prime) {
            break;
        }
        if (max_used / prime <= current_pairs_count - k) {
            elements_to_omit.push_back(prime);
            current_pairs_count -= max_used / prime;
        }
    }
    size_t omit_index = 0;
    std::cout << max_used - static_cast<int>(elements_to_omit.size()) << std::endl;
    for (int i = 1; i <= max_used; ++i) {
        if (omit_index == elements_to_omit.size() || i != elements_to_omit[omit_index]) {
            std::cout << i << " ";
        }
        if (omit_index < elements_to_omit.size() && i == elements_to_omit[omit_index]) {
            ++omit_index;
        }
    }
    std::cout << std::endl;
    return 0;
}
