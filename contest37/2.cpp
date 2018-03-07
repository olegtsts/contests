#include <iostream>

void Divide(long long int& m, long long int& n) {
    long long int div_res = m / n / 2 * 2;
    m -= div_res * n;
}

int main() {
    long long int m,n;
    std::cin >> m >> n;
    while (m > 0 && n > 0) {
        if (m >= 2 * n) {
            Divide(m, n);
        } else if (n >= 2 * m) {
            Divide(n, m);
        } else {
            break;
        }
    }
    std::cout << m << " " << n << std::endl;
    return 0;
}
