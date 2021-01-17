#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, d;
        std::cin >> n >> d;
        std::vector<int> a(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> a[j];
        }
        std::sort(a.begin(), a.end());
        if (a[n - 1] <= d || a[0] + a[1] <= d) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
