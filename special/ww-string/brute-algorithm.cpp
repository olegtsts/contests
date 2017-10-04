#include <string>
#include <iostream>

bool IsStringDistinguable(const std::string& input_string, const size_t max_k) {
    for (size_t i = 0; i < input_string.size(); ++i) {
        for (size_t k = 1; i + 2 * k <= input_string.size() && k <= max_k; ++k) {
            if (input_string.substr(i, k) == input_string.substr(i + k, k)) {
                return false;
            }
        }
    }
    return true;
}

std::string GetStartingString(const int n) {
    return std::string(n, 'a');
}

bool IterateString(std::string& input_string, const int n, const int a) {
    for (size_t i = 0; i < input_string.size(); ++i) {
        ++input_string[i];
        if (input_string[i] - 'a' >= a) {
            input_string[i] = 'a';
        } else {
            return true;
        }
    }
    return false;
}

long long int GetDistinguableCountsTest(const int k, const int a, const int n) {
    long long int distinguable_strings_count = 0;
    std::string input_string = GetStartingString(n);
    do {
        if (IsStringDistinguable(input_string, k)) {
            ++distinguable_strings_count;
//            std::cout << input_string << " " << true << std::endl;
        } else {
//            std::cout << input_string << " " << false << std::endl;
        }
    } while (IterateString(input_string, n, a));
    return distinguable_strings_count;
}

int main() {
    int k = 3;
    int n = 5;
    int a = 3;
    std::cin >> k >> n >> a;
    std::cout << GetDistinguableCountsTest(k, a, n) << std::endl;
    return 0;
}
