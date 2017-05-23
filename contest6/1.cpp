#include <iostream>
#include <string>

int main () {
    std::string string;
    std::cin >> string;

    size_t sequent_letters = 0;
    size_t vk_count = 0;
    char prev_letter = '\0';
    bool replacement_used = false;
    for (size_t i = 0; i < string.length(); ++i) {
        char symbol = string[i];
        if (symbol != prev_letter) {
            sequent_letters = 0;
        }
        ++sequent_letters;
        if (symbol == 'K' && prev_letter == 'V') {
            ++vk_count;
        }
        if (
            (
                sequent_letters == 3
                || (sequent_letters == 2 && symbol == 'V' && i + 1 == string.length())
                || (sequent_letters == 2 && symbol == 'K' && i == 1)
            )
            && !replacement_used
        ) {
            ++vk_count;
            replacement_used = true;
        }
        prev_letter = symbol;
    }

    std::cout << vk_count << std::endl;
    return 0;
}
