#include <algorithm>
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<char, int> char_counts;
    int n;
    std::cin >> n;
    size_t max_count = 0;
    for (int i = 0; i < n; ++i) {
        char ch;
        std::cin >> ch;
        if (ch >= 'A' && ch <= 'Z') {
            char_counts.clear();
        } else if (char_counts.count(ch)) {
            ++char_counts[ch];
        } else {
            char_counts[ch] = 1;
        }
        if (max_count < char_counts.size()) {
            max_count = char_counts.size();
        }
    }
    std::cout << max_count << std::endl;
    return 0;
}

