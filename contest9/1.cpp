#include <iostream>
#include <vector>

int main() {
    long long int n;
    std::cin >> n;
    std::vector<long long int> indices(n);
    for (size_t i = 0; i < n; ++i) {
        long long int number;
        std::cin >> number;
        indices[number - 1] = i;
    }

    long long int iterations = 1;
    for (size_t i = 0; i + 1 < n; ++i) {
        if (indices[i] > indices[i + 1]) {
            ++iterations;
        }
    }

    std::cout << iterations << std::endl;

    return 0;
}
