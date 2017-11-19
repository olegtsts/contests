#include <iostream>
#include <string>

int main() {
    int q = 0;
    int qa = 0;
    int qaq = 0;
    std::string input_string;
    std::getline(std::cin, input_string);
    for (auto& ch: input_string) {
        if (ch == 'Q') {
            ++q;
            qaq += qa;
        } else if (ch == 'A')  {
            qa += q;
        }
    }
    std::cout << qaq << std::endl;
    return 0;
}
