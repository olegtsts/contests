#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> names;
    for (char first_symbol = 'A'; first_symbol <= 'Z'; ++first_symbol) {
        for (char second_symbol = 'a'; second_symbol <= 'z'; ++second_symbol) {
            names.push_back(std::string(1, first_symbol) + std::string(1, second_symbol));
        }
    }
    int n,k;
    std::cin >> n >> k;
    std::vector<std::string> used_names;

    for (size_t i = 0; i < k - 1; ++i) {
        used_names.push_back(names[i]);
    }

    for (size_t i = k - 1; i < n; ++i) {
        std::string word;
        std::cin >> word;
        if (word == "YES") {
            used_names.push_back(names[i]);
        } else {
            used_names.push_back(used_names[i - (k - 1)]);
        }
    }
    bool first = true;
    for (auto& name: used_names) {
        if (!first) {
            std::cout << " ";
        }
        first = false;
        std::cout << name;
    }

    std::cout << std::endl;
    return 0;
}
