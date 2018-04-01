#include <cmath>
#include <iostream>

long long int MODULO = 1000000007;

long long int GetPower(const long long int n, const int input_power) {
    long long int result = 1;
    for (int i = 0; i < input_power; ++i) {
        result *= n;
        result %= MODULO;
    }
    return result;
}

long long int Sum2(const long long int n) {
    long long int result = 0;
    result += 2 * GetPower(n, 3);
    result %= MODULO;
    result += 3 * GetPower(n, 2);
    result %= MODULO;
    result += n;
    result %= MODULO;
    result *= 166666668ll; //6
    result %= MODULO;
    return result;
}

long long int Sum4(const long long int n) {
    long long int result = 0;
    result += 6 * GetPower(n, 5);
    result %= MODULO;
    result += 15 * GetPower(n, 4);
    result %= MODULO;
    result += 10 * GetPower(n, 3);
    result %= MODULO;
    result -= n;
    result %= MODULO;
    result += MODULO;
    result %= MODULO;
    result *= 233333335ll; //30
    result %= MODULO;
    return result;
}

long long int Sum6(const long long int n) {
    long long int result = 0;
    result += 6 * GetPower(n, 7);
    result %= MODULO;
    result += 21 * GetPower(n, 6);
    result %= MODULO;
    result += 21 * GetPower(n, 5);
    result %= MODULO;
    result -= 7 * GetPower(n, 3);
    result %= MODULO;
    result += MODULO;
    result %= MODULO;
    result += n;
    result %= MODULO;
    result *= 23809524ll; //42
    result %= MODULO;
    return result;
}

void UpdateSums(long long int& s0, long long int& s1, long long int& s2, long long int& s3, const long long int x, const long long int n) {
        long long int main_sqrt = static_cast<long long int>(sqrt(n - x * x));
        s0 += 2 * main_sqrt + 1;
        s0 %= MODULO;

        long long int s1_addon = 1;
        s1_addon *= GetPower(x, 2);
        s1_addon %= MODULO;
        s1_addon *= (2 * main_sqrt + 1);
        s1_addon %= MODULO;
        s1_addon += 2 * Sum2(main_sqrt);
        s1_addon %= MODULO;
        s1 += s1_addon;
        s1 %= MODULO;

        long long int s2_first_addon = 1;
        s2_first_addon *= GetPower(x, 4);
        s2_first_addon %= MODULO;
        s2_first_addon *= 2 * main_sqrt + 1;
        s2_first_addon %= MODULO;
        long long int s2_second_addon = 1;
        s2_second_addon *= GetPower(x, 2) * 2;
        s2_second_addon %= MODULO;
        s2_second_addon *= 2 * Sum2(main_sqrt);
        s2_second_addon %= MODULO;
        long long int s2_third_addon = 1;
        s2_third_addon *= 2 * Sum4(main_sqrt);
        s2_third_addon %= MODULO;

        s2 += s2_first_addon;
        s2 %= MODULO;
        s2 += s2_second_addon;
        s2 %= MODULO;
        s2 += s2_third_addon;
        s2 %= MODULO;

        long long int s3_first_addon = 1;
        s3_first_addon *= GetPower(x, 6);
        s3_first_addon %= MODULO;
        s3_first_addon *= 2 * main_sqrt + 1;
        s3_first_addon %= MODULO;
        long long int s3_second_addon = 1;
        s3_second_addon *= 3 * GetPower(x, 4);
        s3_second_addon %= MODULO;
        s3_second_addon *= 2 * Sum2(main_sqrt);
        s3_second_addon %= MODULO;
        long long int s3_third_addon = 1;
        s3_third_addon *= 3 * GetPower(x, 2);
        s3_third_addon %= MODULO;
        s3_third_addon *= 2 * Sum4(main_sqrt);
        s3_third_addon %= MODULO;
        long long int s3_forth_addon = 1;
        s3_forth_addon *= 2 * Sum6(main_sqrt);
        s3_forth_addon %= MODULO;

        s3 += s3_first_addon;
        s3 %= MODULO;
        s3 += s3_second_addon;
        s3 %= MODULO;
        s3 += s3_third_addon;
        s3 %= MODULO;
        s3 += s3_forth_addon;
        s3 %= MODULO;
}

int main() {
    long long int n;
    std::cin >> n;
    long long int s0 = 0;
    long long int s1 = 0;
    long long int s2 = 0;
    long long int s3 = 0;

    for (long long int x = 1; x <= static_cast<long long int>(sqrt(n)); ++x) {
        UpdateSums(s0, s1, s2, s3, x, n);
    }
    s0 *= 2;
    s0 %= MODULO;
    s1 *= 2;
    s1 %= MODULO;
    s2 *= 2;
    s2 %= MODULO;
    s3 *= 2;
    s3 %= MODULO;

    UpdateSums(s0, s1, s2, s3, 0, n);

    long long int result_first_addon = 1;
    result_first_addon *= (n % MODULO);
    result_first_addon %= MODULO;
    result_first_addon *= (n % MODULO) + 1;
    result_first_addon %= MODULO;
    result_first_addon *= (n % MODULO) + 2;
    result_first_addon %= MODULO;
    result_first_addon *= s0;
    result_first_addon %= MODULO;
    result_first_addon *= 166666668ll; //6
    result_first_addon %= MODULO;
    long long int result_second_addon = MODULO - 1;
    result_second_addon *= (n % MODULO) + 1;
    result_second_addon %= MODULO;
    result_second_addon *= (s2 - s1);
    result_second_addon %= MODULO;
    result_second_addon += MODULO;
    result_second_addon %= MODULO;
    result_second_addon *= 500000004ll; //2
    result_second_addon %= MODULO;
    long long int result_third_addon = 0;
    result_third_addon += 2 * s3;
    result_third_addon %= MODULO;
    result_third_addon += -3 * s2;
    result_third_addon %= MODULO;
    result_third_addon += MODULO;
    result_third_addon %= MODULO;
    result_third_addon += s1;
    result_third_addon %= MODULO;
    result_third_addon *= 166666668ll; //6
    result_third_addon %= MODULO;

    long long int result = 0;
    result += result_first_addon;
    result %= MODULO;
    result += result_second_addon;
    result %= MODULO;
    result += result_third_addon;
    result %= MODULO;

    std::cout << result << std::endl;
}
