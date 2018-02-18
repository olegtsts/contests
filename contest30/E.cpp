#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

int main() {
    long long int n,k;
    std::cin >> n >> k;
    std::vector<std::string> text(n);
    std::unordered_map<std::string, long long int> words;
    for (long long int i = 0; i < n; ++i) {
        std::cin >> text[i];
    }
    for (long long int j = 0; j < k; ++j) {
        std::string word;
        std::cin >> word;
        words[word] = j;
    }
    long long int result = 0;
    long long int begin_index = 0;
    long long int end_index = 0;
    std::vector<int> word_index_usage_counter(k, 0);
    long long int words_used = 0;
    while (begin_index < n) {
        while (end_index < n && words_used < k) {
            auto& next_word = text[end_index++];
            if (words.count(next_word) > 0) {
                auto word_index = words[next_word];
                if (!word_index_usage_counter[word_index]) {
                    ++words_used;
                }
                ++word_index_usage_counter[word_index];
            }
        }
        if (words_used < k) {
            break;
        }
        result += n - end_index + 1;
        auto& lost_word = text[begin_index];
        if (words.count(lost_word) > 0) {
            auto word_index = words[lost_word];
            --word_index_usage_counter[word_index];
            if (!word_index_usage_counter[word_index]) {
                --words_used;
            }
        }
        ++begin_index;
    }
    std::cout << result << std::endl;
    return 0;
}
