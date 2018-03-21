#include <algorithm>
#include <iostream>

int main() {
    int l,a,r;
    std::cin >> l >> r >> a;
    int result = std::min(l, r);
    l -= result;
    r -= result;
    if (a >= std::max(l, r)) {
        result += std::max(l, r) + (a - std::max(l, r)) / 2;
    } else {
        result += a;
    }
    std::cout << 2 * result << std::endl;
    return 0;
}
