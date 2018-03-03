#include <iostream>
#include <vector>
#include <string>

int Pack(const int mask, const int prefix_abc, const int last_letter_number) {
    int index = mask;
    index *= 11;
    index += prefix_abc;
    index *= 11;
    index += last_letter_number;
    return index;
}

int main() {
    std::vector<long long int> dp(123904, 0);
    std::string input_string;
    std::cin >> input_string;
    for (size_t i = 0; i < input_string.size(); ++i) {
        int number = input_string[i] - '0';
        std::vector<long long int> new_dp(123904, 0);
        for (int mask = 0; mask < 1024; ++mask) {
            for (int prefix_abc = 1; prefix_abc <= 10; ++prefix_abc) {
                for (int last_letter_number = 0; last_letter_number < 10; ++last_letter_number) {
                    if ((mask & (1 << number)) == 0) {
                        new_dp[Pack(mask, prefix_abc, last_letter_number)] += dp[Pack(mask, prefix_abc, last_letter_number)];
                    } else {
                        if ((mask & (1 << last_letter_number))) {
                            if (number == last_letter_number) {
                                if (prefix_abc > 1) {
                                    for (int another_last_letter_number = 0; another_last_letter_number < 10; ++another_last_letter_number) {
                                        new_dp[Pack(mask, prefix_abc, last_letter_number)] +=
                                            dp[Pack(mask & ~(1 << number), prefix_abc - 1, another_last_letter_number)];
                                    }
                                } else {
                                    new_dp[Pack(mask, prefix_abc, last_letter_number)] += 1;
                                }
                            } else {
                                new_dp[Pack(mask, prefix_abc, last_letter_number)] += dp[Pack(mask, prefix_abc, last_letter_number)];
                            }
                        }
                    }
                }
            }
        }
        dp = std::move(new_dp);
    }
    long long int result = 0;
    for (int last_letter_number = 0; last_letter_number < 10; ++last_letter_number) {
        result += dp[Pack(1023, 10, last_letter_number)];
    }
    std::cout << result << std::endl;
    return 0;
}
