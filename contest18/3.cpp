#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    int n, q, c;
    std::cin >> n >> q >> c;
    std::vector<int> points(112211, 0);
    for (int i = 0; i < n; ++i) {
        int x,y,s;
        std::cin >> x >> y >> s;
        --x;
        --y;
        for (int j = 0; j <= c; ++j) {
            int shining = (s + j) % (c + 1);
            points[j * 10201 + x * 101 + y] += shining;
        }
    }
    std::vector<int> prefix_sums(112211, 0);
    for (int j = 0; j <= c; ++j) {
        for (int k = 1; k < 101; ++k) {
            for (int l = 1; l < 101; ++l) {
                prefix_sums[j * 10201 + k * 101 + l] +=
                    points[j * 10201 + (k - 1) * 101 + l - 1]
                    + prefix_sums[j * 10201 + (k - 1) * 101 + l]
                    + prefix_sums[j * 10201 + k * 101 + l - 1]
                    - prefix_sums[j * 10201 + (k - 1) * 101 + l - 1];
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        long long int t;
        int x1,y1,x2,y2;
        std::cin >> t >> x1 >> y1 >> x2 >> y2;
        --x1;
        --x2;
        --y1;
        --y2;
        int shift = t % (c + 1);
        std::cout << (prefix_sums[shift * 10201 + (x2 + 1) * 101 + (y2 + 1)]
                      - prefix_sums[shift * 10201 + (x2 + 1) * 101 + y1]
                      - prefix_sums[shift * 10201 + x1 * 101 + y2 + 1]
                      + prefix_sums[shift * 10201 + x1 * 101 + y1]) << std::endl;
    }
    return 0;
}
