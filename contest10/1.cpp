#include <iostream>
#include <algorithm>

int main() {
    int n,k;
    std::cin >> n >> k;
    long long int s;
    for (int i = 0; i < n; ++i) {
        int mark;
        std::cin >> mark;
        s += mark;
    }
    long long int answer = 2 * (n * k - s) - n;
    if (answer < 0) {
        answer = 0;
    }
    std::cout << answer << std::endl;
    return 0;
}
