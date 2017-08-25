#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end(), [] (const int a, const int b) -> bool {return a > b;});
    std::cout << ((a[n - 1] > a[n]) ? "YES\n" : "NO\n");
    return 0;
}
