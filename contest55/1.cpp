#include <iostream>
#include <vector>
#include <algorithm>

struct Ratio {
    long long int numerator;
    long long int denominator;

    bool IsUpperRounded() const {
        return (numerator % denominator) * 2 >= denominator;
    }
    long long int GetIntegralPart() const {
        return numerator / denominator;
    }
    void LeaveNotIntegralPart() {
        numerator %= denominator;
    }
};


long long int DoTest() {
    long long int n,l;
    std::cin >> n >> l;
    std::vector<Ratio> ratios;
    long long int result = 0;
    long long int addons_remain = n;
    for (long long int i = 0; i < l; ++i) {
        Ratio input_ratio;
        std::cin >> input_ratio.numerator;
        addons_remain -= input_ratio.numerator;
        input_ratio.numerator *= 100;
        input_ratio.denominator = n;
        result += input_ratio.GetIntegralPart();
//        std::cout << "increased by " << input_ratio.GetIntegralPart() << std::endl;
        input_ratio.LeaveNotIntegralPart();
        if (input_ratio.IsUpperRounded()) {
            result += 1;
//            std::cout << "increased by 1\n";
        } else {
            ratios.push_back(input_ratio);
        }
    }
    std::sort(ratios.begin(), ratios.end(), [](const Ratio& first, const Ratio& second) {
        return first.numerator > second.numerator;
    });
    size_t ratio_index = 0;
    while (addons_remain > 0) {
        if (ratio_index >= ratios.size()) {
            ratios.push_back({0, n});
        }
        auto current_ratio = ratios[ratio_index];
        while (addons_remain > 0 && !current_ratio.IsUpperRounded()) {
            current_ratio.numerator += 100;
            result += current_ratio.GetIntegralPart();
//            std::cout << "increased by " << current_ratio.GetIntegralPart() << std::endl;
            current_ratio.LeaveNotIntegralPart();
            --addons_remain;
        }
        if (current_ratio.IsUpperRounded()) {
            result += 1;
//            std::cout << "increased by 1\n";
        } else {
            break;
        }
        ++ratio_index;
    }
    return result;
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
