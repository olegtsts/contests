#include <iostream>
#include <algorithm>

int main () {
    int n;
    std::cin >> n;
    std::vector<int> values(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> values[i];
    }
    std::sort(values.begin(), values.end());
    std::vector<int> minimums(n, n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j >= 0; --j) {
            if (values[j] + 2 >= values[i]) {
                int pairs = (i - j + 2) / 2;
    //            std::cout << " i = " << i << " j = " << j << " pre pairs = " << pairs << std::endl;
                if (j >= 1) {
    //                std::cout << "addon = " << minimums[j - 1] << std::endl;
                    pairs += minimums[j - 1];
                }
//                std::cout << " i = " << i << " j = " << j << " pairs = " << pairs << std::endl;
                if (minimums[i] > pairs) {
                    minimums[i] = pairs;
                }
            } else {
                break;
            }
        }
    }

    std::cout << minimums[n - 1] << std::endl;

    return 0;
}
