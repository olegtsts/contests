#include <iostream>
#include <algorithm>

int main() {
    std::vector<long long int> factorials{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880l, 3628800l, 39916800l, 479001600l};
    long long int a,b;
    std::cin >> a >> b;
    std::cout << factorials[std::min(a, b)] << std::endl;
    return 0;
}
