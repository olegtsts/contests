#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

template <typename Iterator>
long long int getProduct(Iterator it, int k) {
    long long int product = 1;
    for (int i = 0; i < k; ++i) {
        product *= *it++;
    }
    return product;
}

long long int SolveTest() {
    int n;
    std::cin >> n;
    std::vector<long long int> positives;
    std::vector<long long int> negatives;
    for (int i = 0; i < n; ++i) {
        long long int number;
        std::cin >> number;
        if (number >= 0) {
            positives.push_back(number);
        } else {
            negatives.push_back(number);
        }
    }
    std::sort(positives.begin(), positives.end(), [](int first, int second) {return first < second;});
    std::sort(negatives.begin(), negatives.end(), [](int first, int second) {return first > second;});
    long long int max_product = std::numeric_limits<long long int>::min();
    for (int positives_count = 0; positives_count <= 5; ++positives_count) {
        if (positives_count <= static_cast<int>(positives.size()) && 5 - positives_count <= static_cast<int>(negatives.size())) {
            if (positives_count % 2 == 0) {
                max_product = std::max(max_product, getProduct(positives.rbegin(), positives_count) * getProduct(negatives.begin(), 5 - positives_count));
            } else {
                max_product = std::max(max_product, getProduct(positives.rbegin(), positives_count) * getProduct(negatives.rbegin(), 5 - positives_count));
            }
        }
    }
    return max_product;
}

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << SolveTest() << std::endl;
    }
}
