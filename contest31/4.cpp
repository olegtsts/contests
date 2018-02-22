#include <iostream>
#include <vector>
#include <numeric>

long long int MODULO = 1000000007;

long long int GetPower(long long int base, int input_power) {
    long long int result = 1;
    while (input_power) {
        if (input_power % 2 == 0) {
            base *= base;
            base %= MODULO;
            input_power /= 2;
        } else {
            result *= base;
            result %= MODULO;
            input_power -= 1;
        }
    }
    return result;
}

long long int gcd (long long int a, long long int b, long long int & x, long long int & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	long long int x1, y1;
	long long int d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

long long int GetInverse(long long int number) {
    long long int x;
    long long int y;
    gcd(number, MODULO, x, y);
    x %= MODULO;
    x += MODULO;
    x %= MODULO;
    return x;
}

int main() {
    std::ios::sync_with_stdio(false);
    long long int m;
    int n;
    std::cin >> n >> m;
    std::vector<long long int> s1(n);
    std::vector<long long int> s2(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s1[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> s2[i];
    }
    long long int accumulated_prob_nominator = 0;
    int power_of_dem = 0;
    for (int i = 0; i < n; ++i) {
        if (s1[i] == 0 && s2[i] == 0) {
            accumulated_prob_nominator *= m;
            accumulated_prob_nominator %= MODULO;
            ++power_of_dem;
            accumulated_prob_nominator += m - 1;
        } else if (s1[i] == 0) {
            accumulated_prob_nominator *= m;
            accumulated_prob_nominator %= MODULO;
            ++power_of_dem;
            accumulated_prob_nominator += 2 * (m - s2[i]);
        } else if (s2[i] == 0) {
            accumulated_prob_nominator *= m;
            ++power_of_dem;
            accumulated_prob_nominator %= MODULO;
            accumulated_prob_nominator += 2 * (s1[i] - 1);
        } else if (s1[i] < s2[i]) {
            break;
        } else if (s1[i] > s2[i]) {
            accumulated_prob_nominator += 2;
            break;
        }
    }
    long long int q_minus = GetInverse(2 * GetPower(m, power_of_dem) % MODULO);

    std::cout << (accumulated_prob_nominator * q_minus) % MODULO << std::endl;
    return 0;
}
