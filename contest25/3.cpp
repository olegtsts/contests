#include <vector>
#include <iostream>
#include <string>

int main() {
    std::vector<long long int > lengths(56, 0);
    long long int power_of_two = 1;
    long long int d = 68;
    long long int f0 = 75;
    for (size_t i = 0; i <= 55; ++i) {
        lengths[i] = d * (power_of_two - 1) + f0 * power_of_two;
        power_of_two *= 2;
    }
    int q;
    std::cin >> q;
    long long int a = 34;
    long long int b = 32;
    long long int c = 2;
    std::string first_part = "What are you doing while sending \"";
    std::string second_part = "\"? Are you busy? Will you send \"";
    std::string third_part = "\"?";
    std::string initial = "What are you doing at the end of the world? Are you busy? Will you save us?";

    for (int i = 0; i < q; ++i) {
        long long int n, k;
        std::cin >> n >> k;
        --k;
        while (n > 0) {
            if (k < a) {
                std::cout << first_part[k];
                break;
            } else {
                k -= a;
                if (n >= 56 || k < lengths[n - 1]) {
                    --n;
                } else {
                    k -= lengths[n - 1];
                    if (k < b) {
                        std::cout << second_part[k];
                        break;
                    } else {
                        k -= b;
                        if (n >= 56 || k < lengths[n - 1]) {
                            --n;
                        } else {
                            k -= lengths[n - 1];
                            if (k < c) {
                                std::cout << third_part[k];
                                break;
                            } else {
                                std::cout << ".";
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (n == 0) {
            if (k < lengths[0]) {
                std::cout << initial[k];
            } else {
                std::cout << ".";
            }
        }
    }
    return 0;
}
