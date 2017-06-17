#include <iostream>

int invert(const int a) {
    int first_digit = a / 10;
    int second_digit = a % 10;
    return second_digit * 10 + first_digit;
}

int iterated_hour(const int a) {
    return (a + 1) % 24;
}

bool is_ok_invertible(const int a) {
    int second_digit = a % 10;
    return second_digit <= 5;
}

int main() {
    int a, b;
    char ch;
    std::cin >> a >> ch >> b;
    int result_minutes = 0;
    if (invert(a) < b || !is_ok_invertible(a)) {
        a = iterated_hour(a);
        result_minutes += 60;
    }
    while (!is_ok_invertible(a)) {
        a = iterated_hour(a);
        result_minutes += 60;
    }
    result_minutes += invert(a) - b;
    std::cout << result_minutes << std::endl;
    return 0;
}
