#include <iostream>
#include <vector>

long long int MODULO = 1000000007;

long long int gcd(const long long int a,
    const long long int b,
    long long int& x,
    long long int& y
) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long int x1;
    long long int y1;
    int d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

long long int reverse(const long long int number) {
    long long int x,y;
    gcd(number, MODULO, x, y);
    return x;
}

template <typename T>
long long int evaluate_special(
    T begin,
    const int n
) {
    int degree = (n - 1) / 2;
    long long int first_coeff = 1;
    long long int result = 0;

    for (int i = 0; i < degree + 1; ++i) {
        result += first_coeff * *begin;
        result %= MODULO;
        if (i < degree) {
            first_coeff *= degree - i;
            first_coeff %= MODULO;
            first_coeff *= reverse(i + 1);
            first_coeff %= MODULO;
        }
        ++begin;
        ++begin;
    }
    return result;
}

long long int evaluate(
    std::vector<long long int>& numbers,
    bool is_plus
) {
    if (numbers.size() > 1) {
        std::vector<long long int> new_numbers(static_cast<int>(numbers.size()) - 1);
        for (size_t i = 0; i + 1 < numbers.size(); ++i) {
            new_numbers[i] = numbers[i] + (is_plus ? 1 : -1) * numbers[i + 1];
            new_numbers[i] %= MODULO;
            is_plus = !is_plus;
        }
        return evaluate(new_numbers, is_plus);
    } else {
        return numbers[0];
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<long long int> numbers(n, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    int k = (n - 1) / 4 * 4 + 1;
    std::vector<long long int> special_numbers(n - k + 1, 0);
    auto it = numbers.begin();
    for (int i = 0; i < n - k + 1; ++i) {
        special_numbers[i] = evaluate_special(it++, k);
    }
    long long int result = evaluate(special_numbers, true);
    result += MODULO;
    result %= MODULO;
    std::cout << result << std::endl;
    return 0;
}
