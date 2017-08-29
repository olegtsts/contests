#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    long long int k;
    std::cin >> k;
    std::string s;
    std::cin >> s;
    long long int sum = 0;
    std::sort(s.begin(), s.end());
    auto it = s.begin();
    long long int result = 0;
    for (auto& sym: s) {
        sum += sym - '0';
    }
    while (sum < k && it != s.end()) {
        sum += '9' - *it++;
        ++result;
    }
    std::cout << result << std::endl;
    return 0;
}
