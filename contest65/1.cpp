#include <iostream>
#include <vector>

int SolveTest() {
    int n;
    std::cin >> n;
    std::vector<int> number_counts(102, 0);
    for (int i = 0; i < n; ++i) {
        int number;
        std::cin >> number;
        ++number_counts[number];
    }
    for (int number = 0; number <= 101; ++number) {
        if (number_counts[number] == 0) {
            return 2 * number;
        } else if (number_counts[number] == 1) {
            for (int other_number = number + 1; other_number <= 101; ++other_number) {
                if (number_counts[other_number] == 0) {
                    return number + other_number;
                }
            }
        }
    }
    return 0;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << SolveTest() << std::endl;
    }
    return 0;
}
