#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<bool> is_number_used(601, false);
    for (int i = 0 ; i < n; ++i ){
        int number;
        std::cin >> number;
        is_number_used[number] = true;
    }
    int counter = 0;
    for (int i = 1; i <= 600; ++i) {
        if (is_number_used[i]) {
            ++counter;
        }
    }
    std::cout << counter << std::endl;
    return 0;
}
