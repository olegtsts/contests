#include <iostream>
#include <unordered_set>

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;
        std::unordered_set<long long int> elements;
        for (int j = 0; j < n; ++j) {
            long long int element;
            std::cin >> element;
            elements.insert(element);
        }
        std::cout << elements.size() << std::endl;
    }
    return 0;
}
