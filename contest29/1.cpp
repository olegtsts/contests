#include <iostream>
#include <string>

bool IsVowel(const char symbol) {
    return symbol == 'a' || symbol == 'e' || symbol == 'i' || symbol == 'o' || symbol == 'u' || symbol == 'y';
}

int main() {
    int n;
    std::cin >> n;
    std::string input_string;
    std::cin >> input_string;
    std::string output_string;
    bool prev_was_vowel = false;
    for (size_t i = 0; i < input_string.size(); ++i) {
        if (!(prev_was_vowel && IsVowel(input_string[i]))) {
            output_string.push_back(input_string[i]);
        }
        prev_was_vowel = IsVowel(input_string[i]);
    }
    std::cout << output_string << std::endl;
    return 0;
}
