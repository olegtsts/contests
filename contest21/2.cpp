#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <utility>

int main() {
    std::string s;
    std::getline(std::cin, s);
    std::getline(std::cin, s);
    std::vector<std::pair<int, int>> balances(s.size() * 2 + 1, std::make_pair(INT_MAX, INT_MIN));
    int balance_shift = static_cast<int>(s.size()) + 1;
    int current_balance = 0;
    balances[0 + balance_shift] = std::make_pair(-1, -1);
    for (int i = 0; i < static_cast<int>(s.size()); ++i){
        char symbol = s[i];
        if (symbol == '1') {
            ++current_balance;
        } else {
            --current_balance;
        }
        if (i < balances[current_balance + balance_shift].first) {
            balances[current_balance + balance_shift].first = i;
        }
        if (i > balances[current_balance + balance_shift].second) {
            balances[current_balance + balance_shift].second = i;
        }
    }
    int longest_balanced = 0;
    for (auto& min_and_max: balances) {
        if (min_and_max.first != INT_MAX && min_and_max.second != INT_MIN && longest_balanced < min_and_max.second - min_and_max.first) {
            longest_balanced = min_and_max.second - min_and_max.first;
        }
    }
    std::cout << longest_balanced << std::endl;
    return 0;
}
