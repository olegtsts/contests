#include <iostream>
#include <string>

int GetBitCount(int64_t number) {
    int bit_count = 0;
    while (number > 0) {
        bit_count += 1;
        number &= (number - 1);
    }
    return bit_count;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    uint64_t letters_mask = (1 << 26) - 1;
    bool letter_is_known = false;
    size_t shocks_count = 0;
    for (int i = 0; i < n; ++i) {
        if (letter_is_known) {
            char action;
            std::cin >> action;
            std::string rest;
            std::cin >> rest;
            if (action == '!' || (action == '?' && i + 1 < n)) {
                ++shocks_count;
            }
        } else {
            char action;
            std::cin >> action;
            if (action == '!') {
                std::string word;
                std::cin >> word;
                uint64_t mask = 0;
                for (auto& symbol: word) {
                    mask |= (1 << (symbol - 'a'));
                }
//                std::cout << "incr " << mask << std::endl;
                letters_mask &= mask;
            } else if (action == '.') {
                std::string word;
                std::cin >> word;
                uint64_t mask = 0;
                for (auto& symbol: word) {
                    mask |= (1 << (symbol - 'a'));
                }
//                std::cout << "decr " << mask << std::endl;
                letters_mask &= (~mask);
            } else if (action == '?') {
                char symbol;
                std::cin >> symbol;
                if (i + 1 < n) {
//                    std::cout << "remove one letter " << symbol << std::endl;
                    letters_mask &= (~(1ull << (symbol - 'a')));
                } else {
//                    std::cout << "add one letter " << symbol << std::endl;
                    letters_mask = (1ull << (symbol - 'a'));
                }
            }
            if (GetBitCount(letters_mask) == 1) {
                letter_is_known = true;
            }
//            std::cout << letters_mask << " " << letter_is_known  << std::endl;
        }
    }
    std::cout << shocks_count << std::endl;
    return 0;
}
