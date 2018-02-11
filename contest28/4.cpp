#include <iostream>

long long int phi (long long int n) {
	long long int result = n;
	for (long long int i=2; i*i<=n; ++i)
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
	if (n > 1)
		result -= result / n;
	return result;
}
int main() {
    long long int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << 2 << std::endl;
        return 0;
    }
    std::cout << phi(n) << std::endl;
    return 0;
}
