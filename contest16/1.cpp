#include <algorithm>
#include <iostream>
#include <unordered_map>

int main() {
    int n,k;
    std::cin >> n >> k;
    std::unordered_map<char, int> letter_counts;
    for (int i = 0; i < n; ++i) {
        char ch;
        std::cin >> ch;
        if (letter_counts.count(ch) == 0) {
            letter_counts[ch] = 0;
        }
        ++letter_counts[ch];
        if (letter_counts[ch] > k) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    return 0;
}
