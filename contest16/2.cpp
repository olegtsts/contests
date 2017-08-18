#include <iostream>
#include <string>

int main() {
    int n;
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    std::string s;
    for (int i = 0; i < n; ++i) {
        long long int a;
        std::cin >> a;
        if (a % 2 == 1) {
            std::cout << "First\n";
            return 0;
        }
    }
    std::cout << "Second\n";
    return 0;
}
