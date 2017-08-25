#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers(6);
    for (int i = 0; i < 6; ++i) {
        char ch;
        std::cin >> ch;
        numbers[i] = ch - '0';
    }
    int first_sum = 0;
    int second_sum = 0;
    for (int i = 0; i < 6; ++i) {
        if (i < 3) {
            first_sum += numbers[i];
        } else {
            second_sum += numbers[i];
        }
    }
    if (first_sum > second_sum) {
        for (int i = 0; i < 3; ++i) {
            std::swap(numbers[i], numbers[i + 3]);
        }
    }
    int difference = abs(first_sum - second_sum);
    for (int i = 0; i < 3; ++i) {
        numbers[i] = 9 - numbers[i];
    }
    std::sort(numbers.begin(), numbers.end(), [] (const int a, const int b) -> bool {return a > b;});
    int total_needed_changes = 0;
    while (difference > 0) {
        difference -= numbers[total_needed_changes++];
    }
    std::cout << total_needed_changes << std::endl;
    return 0;
}
