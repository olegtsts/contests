#include <numeric>
#include <iostream>
#include <vector>

long long int MODULO = 1000000009;

long long int GetPower(long long int base, long long int input_power) {
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
	long long int  n,a,b,k;
    std::cin >> n >> a >> b >> k;
    long long int inverse_a = GetInverse(a);
    std::vector<int> signs(k);
    for (long long int i = 0; i < k; ++i) {
        char ch;
        std::cin >> ch;
        if (ch == '+') {
            signs[i] = 1;
        } else {
            signs[i] = MODULO - 1;
        }
    }
    long long int first_mult = GetPower(a, n);
    long long int second_mult = 1;
    long long int x = 0;
    for (long long i = 0; i < k; ++i) {
        long long int addon = signs[i];
        addon *= first_mult;
        addon %= MODULO;
        addon *= second_mult;
        addon %= MODULO;
        x += addon;
        x %= MODULO;
        first_mult *= inverse_a;
        first_mult %= MODULO;
        second_mult *= b;
        second_mult %= MODULO;
    }
    long long int m = (n + 1) / k;
    long long int b_over_a = b * inverse_a;
    b_over_a %= MODULO;
    long long int result;
    long long int b_over_a_in_k = GetPower(b_over_a, k);
    if (b_over_a_in_k == 1) {
        result = x * m % MODULO;
    } else {
        long long int b_over_a_in_k_minus_1 = (b_over_a_in_k - 1 + MODULO) % MODULO;
        long long int inverse_b_over_a_in_k_minus_1 = GetInverse(b_over_a_in_k_minus_1);
        long long int b_over_a_in_mk = GetPower(b_over_a_in_k, m);
        long long int b_over_a_in_mk_minus_1 = (b_over_a_in_mk - 1 + MODULO) % MODULO;
        result = x * b_over_a_in_mk_minus_1;
        result %= MODULO;
        result *= inverse_b_over_a_in_k_minus_1;
        result %= MODULO;
    }
    std::cout << result << std::endl;
    return 0;

}

