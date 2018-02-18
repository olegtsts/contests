#include <vector>
#include <iostream>

long long int MakeMask(const std::vector<int>& numbers) {
    long long int mask = 0;
    for (auto& number: numbers) {
        mask |= (1ll << (number - 1));
    }
    return mask;
}

int GetBitCount(long long int number) {
    int bit_count = 0;
    while (number > 0) {
        number &= (number - 1);
        ++bit_count;
    }
    return bit_count;
}

int main() {
    std::vector<int> juri_numbers(10);
    for (int i = 0; i < 10; ++i) {
        std::cin >> juri_numbers[i];
    }
    long long int juri_mask = MakeMask(juri_numbers);
    int n;
    std::cin >> n;
    std::vector<int> user_numbers(6);
    for (int i = 0;i < n; ++i) {
        for (int j = 0; j < 6; ++j) {
            std::cin >> user_numbers[j];
        }
        long long int user_mask = MakeMask(user_numbers);
        if (GetBitCount(user_mask & juri_mask) >= 3) {
            std::cout << "Lucky\n";
        } else {
            std::cout << "Unlucky\n";
        }
    }
    return 0;
}
