#include <iostream>
#include <string>

int main() {
    int word_sound = 0;
    int text_sound = 0;
    std::string text;
    std::getline(std::cin, text);
    std::getline(std::cin, text);
    for (size_t i = 0; i < text.size(); ++i) {
        char ch = text[i];
        if (ch == ' ') {
            if (text_sound < word_sound) {
                text_sound = word_sound;
            }
            word_sound = 0;
        } else if (ch >= 'A' && ch <= 'Z') {
            ++word_sound;
        }
    }
    if (text_sound < word_sound) {
        text_sound = word_sound;
    }
    std::cout << text_sound << std::endl;
    return 0;
}
