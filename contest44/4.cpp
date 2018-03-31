#include <iostream>
#include <tuple>

std::tuple<long long int, long long int> DoTest() {
    long long int n,k;
    std::cin >> n >> k;
    long long int lower_length = n;
    long long int lower_count = 1;
    long long int upper_count = 0;
    while (k > lower_count + upper_count) {
        k -= lower_count;
        k -= upper_count;
        if (lower_length % 2 == 0) {
            upper_count *= 2;
            upper_count += lower_count;
        } else {
            lower_count *= 2;
            lower_count += upper_count;
        }
        lower_length = (lower_length - 1) / 2;
    }
    if (k <= upper_count) {
        return std::make_tuple((lower_length + 1) / 2, lower_length / 2);
    } else {
        return std::make_tuple(lower_length / 2, (lower_length - 1) / 2);
    }
}
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        long long int first_number,second_number;
        std::tie(first_number, second_number) = DoTest();
        std::cout << "Case #" << i + 1 << ": " << first_number << " " << second_number << std::endl;
    }
    return 0;
}
