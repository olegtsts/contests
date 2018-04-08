#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string DoTest() {
    int n;
    std::cin >> n;
    std::vector<long long int> even_numbers((n + 1) / 2);
    std::vector<long long int> odd_numbers(n / 2);
    size_t even_index = 0;
    size_t odd_index = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            std::cin >> even_numbers[even_index++];
        } else {
            std::cin >> odd_numbers[odd_index++];
        }
    }
    std::sort(even_numbers.begin(), even_numbers.end());
    std::sort(odd_numbers.begin(), odd_numbers.end());
    std::vector<long long int> whole_numbers(n);
    even_index = 0;
    odd_index = 0;
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            whole_numbers[i] = even_numbers[even_index++];
        } else {
            whole_numbers[i] = odd_numbers[odd_index++];
        }
    }
    int bad_index = -1;
    for (int i = 0; i + 1 < n; ++i) {
        if (whole_numbers[i] > whole_numbers[i + 1]) {
            bad_index = i;
            break;
        }
    }
    if (bad_index == -1) {
        return "OK";
    } else {
        return std::to_string(bad_index);
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ": " << DoTest() << std::endl;
    }
    return 0;
}
