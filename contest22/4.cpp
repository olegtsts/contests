#include <limits>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

struct WordIndex {
    size_t word_index = std::numeric_limits<size_t>::max();
    size_t letter_offset = std::numeric_limits<size_t>::max();
};

struct WordOffset {
    size_t word_index = std::numeric_limits<size_t>::max();
    int word_offset = std::numeric_limits<int>::max();
};

void dfs(
    std::vector<bool>& is_visited,
    const size_t current_word_index,
    const std::vector<std::vector<WordIndex>>& letter_index,
    const std::vector<std::string>& words,
    const int offset,
    std::vector<WordOffset>& word_offsets
) {
    if (!is_visited[current_word_index]) {
        is_visited[current_word_index] = true;
        word_offsets.push_back({current_word_index, offset});
        for (size_t letter_position = 0; letter_position < words[current_word_index].size(); ++letter_position) {
            char symbol = words[current_word_index][letter_position];
            for (auto& word_index: letter_index[symbol - 'a']) {
                dfs(is_visited, word_index.word_index, letter_index, words, offset + letter_position - word_index.letter_offset, word_offsets);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    size_t n;
    std::cin >> n;
    std::vector<std::vector<WordIndex>> letter_index('z' - 'a' + 1);
    std::vector<std::string> words(n);
    for (size_t i = 0; i < n; ++i) {
        std::string input_string;
        std::cin >> input_string;
        words[i] = input_string;
        std::vector<size_t> current_letter_offset('z' - 'a' + 1, std::numeric_limits<size_t>::max());
        for (size_t i = 0; i < input_string.size(); ++i) {
            char letter = input_string[i];
            if (current_letter_offset[letter - 'a'] == std::numeric_limits<size_t>::max()) {
                current_letter_offset[letter - 'a'] = i;
            } else {
                std::cout << "NO\n";
                return 0;
            }
        }
        for (size_t letter = 'a'; letter <= 'z'; ++letter) {
            size_t index = current_letter_offset[letter - 'a'];
            if (index != std::numeric_limits<size_t>::max()) {
                letter_index[letter - 'a'].push_back({i, index});
            }
        }
    }
    std::vector<bool> is_visited(n, false);
    std::vector<std::string> distinct_words;
    for (size_t i = 0; i < n; ++i) {
        if (!is_visited[i]) {
            std::vector<WordOffset> word_offsets;
            dfs(is_visited, i, letter_index, words, 0, word_offsets);
            int min_offset = std::numeric_limits<int>::max();
            int max_offset = std::numeric_limits<int>::min();
            for (auto& word_offset: word_offsets) {
                if (word_offset.word_offset < min_offset) {
                    min_offset = word_offset.word_offset;
                }
                if (word_offset.word_offset + static_cast<int>(words[word_offset.word_index].size()) > max_offset) {
                    max_offset = word_offset.word_offset + words[word_offset.word_index].size();
                }
            }
            std::string merged_string(max_offset - min_offset, '\0');
            for (auto& word_offset: word_offsets) {
                for (size_t i = 0; i < words[word_offset.word_index].size(); ++i) {
                    char symbol = words[word_offset.word_index][i];
                    int target_position = word_offset.word_offset + i - min_offset;
                    if (merged_string[target_position] != '\0' && merged_string[target_position] != symbol) {
                        std::cout << "NO\n";
                        return 0;
                    }
                    merged_string[target_position] = symbol;
                }
            }
            std::vector<bool> is_met('z' - 'a' + 1, false);
            for (auto& symbol : merged_string) {
                if (is_met[symbol - 'a']) {
                    std::cout << "NO\n";
                    return 0;
                } else {
                    is_met[symbol - 'a'] = true;
                }
            }
            distinct_words.push_back(merged_string);
        }
    }
    std::sort(distinct_words.begin(), distinct_words.end());
    std::string result_word;
    for (auto& word: distinct_words) {
        result_word += word;
    }
    std::cout << result_word << std::endl;
    return 0;
}
