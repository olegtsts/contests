#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

long long int GetSymbolCount(const std::string& input_string, const char symbol) {
    long long int sym_count = 0;
    for (size_t i = 0; i < input_string.size(); ++i) {
        if (input_string[i] == symbol) {
            ++sym_count;
        }
    }
    return sym_count;
}

struct Word {
    long long int s_count;
    long long int h_count;
    std::string input_string;

    Word(const std::string& input_string)
    : s_count(GetSymbolCount(input_string, 's'))
    , h_count(GetSymbolCount(input_string, 'h'))
    , input_string(input_string)
    {}

    bool operator<(const Word& other) const {
        if (s_count == 0 && other.s_count == 0) {
            return h_count < other.h_count;
        } else if (s_count == 0) {
            return false;
        } else if (other.s_count == 0) {
            return true;
        } else {
            return h_count * other.s_count < other.h_count * s_count;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<Word> strings;
    for (int i = 0; i < n; ++i) {
        std::string input_string;
        std::cin >> input_string;
        strings.push_back(Word(input_string));
    }
    std::sort(strings.begin(), strings.end());
    long long int total_count = 0;
    long long int total_s_count = 0;
    for (size_t i = 0; i < strings.size(); ++i) {
        for (size_t j = 0; j < strings[i].input_string.size(); ++j) {
            char symbol = strings[i].input_string[j];
            if (symbol == 's') {
                ++total_s_count;
            } else {
                total_count += total_s_count;
            }
        }
    }
    std::cout << total_count << std::endl;
    return 0;
}
