#include <iostream>
#include <vector>

const int64_t MODULO = 1000000007;

int64_t mod_power(int64_t a, int64_t b) {
    int64_t x = 1;
    while (b > 0) {
        if (b % 2 == 0) {
            a *= a;
            a %= MODULO;
            b /= 2;
        } else {
            x *= a;
            x %= MODULO;
            b -= 1;
        }
    }
    return x;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int64_t> a(n);
    for (int i = 0; i < n ;++i) {
        std::cin >> a[i];
    }
    std::vector<int64_t> cnt(1000001, 0);
    for (int i = 0; i < n; ++i) {
        ++cnt[a[i]];
    }
    for (int i = 1; i < 1000001; ++i) {
        for (int k = 2; k * i < 1000001; ++k) {
            cnt[i] += cnt[i * k];
        }
    }
    std::vector<int64_t> ans(1000001, 0);
    for (int i = 1000001; i >= 2; --i) {
        if (cnt[i] > 0) {
            ans[i] = mod_power(2, cnt[i] - 1);
            ans[i] *= cnt[i];
            ans[i] %= MODULO;
            for (int k = 2; i * k < 1000001; ++k) {
                ans[i] -= ans[i * k];
                ans[i] %= MODULO;
            }
        }
    }
    int64_t result = 0;
    for (int i = 2; i < 1000001; ++i) {
        int64_t addon = i * ans[i];
        addon %= MODULO;
        result += addon;
        result %= MODULO;
    }
    std::cout << result << std::endl;
    return 0;
}
