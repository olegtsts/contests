#include <iostream>

int main() {
    long long int n,k;
    std::cin >> n >> k;
    long long int parts = n / (k + 1);
    long long int remainder = n - parts * (k + 1);
    long long int result = parts * 2;
    if (remainder > 1) {
        result += 2;
    } else if (remainder == 1) {
        result += 1;
    }
    std::cout << result << std::endl;
    return 0;
}
