#include <iostream>

long long int GetCellNumber(long long int k, long long int n) {
    long long int x = 0;
    while (k > 0) {
        if (k == 1) {
            k = n - 2;
            n -= 1;
            x += 1;
        } else {
            long long int l = k / 2;
            k -= 2 * l;
            n -= l;
            x += l;
        }
    }
    return x + 1;
}

int main() {
    long long int n;
    int q;
    std::cin >> n >> q;
    for (int i = 0; i < q; ++i) {
        long long int cell_index;
        std::cin >> cell_index;
        --cell_index;
        std::cout << GetCellNumber(cell_index, n) << std::endl;
    }
    return 0;
}
