#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n,k;
    std::cin >> n >> k;
    std::vector<int> a(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> a[i];
    }
    int one_fields = 0;
    int double_fields = 2 * n;
    int quad_fields = n;
    for (int i = 0; i < k; ++i) {
        if (a[i] % 2 == 1) {
            if (quad_fields > 0) {
                --a[i];
                --quad_fields;
                ++double_fields;
            } else if (double_fields > 0) {
                --a[i];
                --double_fields;
            } else {
                std::cout << "NO\n";
                return 0;
            }
        }
    }
    for (int i = 0; i < k; ++i) {
        if (a[i] >= 4 && quad_fields > 0) {
            int rows = std::min(quad_fields, a[i] / 4);
            a[i] -= rows * 4;
            quad_fields -= rows;
        }
    }
    if (quad_fields > 0) {
        one_fields += quad_fields;
        double_fields += quad_fields;
        quad_fields = 0;
    }
    for (int i = 0; i < k; ++i) {
        int rows = std::min(a[i] / 2, double_fields);
        double_fields -= rows;
        a[i] -= rows * 2;
        rows = std::min(a[i], one_fields);
        one_fields -= rows;
        a[i] -= rows;
    }
    for (int i = 0; i < k; ++i) {
        if (a[i] > 0) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    return 0;
}
