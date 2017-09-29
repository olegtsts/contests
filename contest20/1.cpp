#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int first_number = 0;
    int second_number = 0;
    int first_count = 0;
    int second_count = 0;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        if (a == first_number) {
            ++first_count;
        } else if (a == second_number) {
            ++second_count;
        } else if (first_number == 0) {
            first_number = a;
            ++first_count;
        } else if (second_number == 0) {
            second_number = a;
            ++second_count;
        } else {
            std::cout << "NO\n";
            return 0;
        }
    }
    if (first_count == second_count) {
        std::cout << "YES\n" << first_number << " " << second_number << "\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
