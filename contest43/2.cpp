#include <iostream>
#include <vector>

long long int GetIntegralDivision(const long long int numerator, const long long int denominator) {
    return (numerator - (((numerator % denominator) + denominator) % denominator)) / denominator;
}

int main() {
    long long int p,k;
    std::cin >> p >> k;
    std::vector<long long int> v;
    long long int initial_p = p;
    while (p != 0) {
        p = -GetIntegralDivision(p, k);
        if (p != 0) {
            v.push_back(p);
        }
    }
    std::vector<long long int> v2(v.size() + 1);
    for (size_t i = 0; i < v.size(); ++i) {
        v2[i] += k * v[i];
        v2[i + 1] += v[i];
    }
    v2[0] += initial_p;
    std::cout << v2.size() << std::endl;
    for (auto& el: v2) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    return 0;
}
