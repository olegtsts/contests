#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

int main() {
    int n,m;
    int c;
    std::cin >> n >> m >> c;
    std::vector<int> forward_pointers(c / 2, 0);
    std::vector<int> backward_pointers((c + 1) / 2, n);
    while (true) {
        int number;
        std::cin >> number;
        --number;
        int cell;
        if (number < c / 2) {
            cell = forward_pointers[number];
            forward_pointers[number]++;
            for (int i = number + 1; i < c / 2; ++i) {
                forward_pointers[i] = std::max(forward_pointers[i], forward_pointers[i - 1]);
            }
        } else {
            number -= c / 2;
            backward_pointers[number]--;
            cell = backward_pointers[number];
            for (int i = number - 1; i >= 0; --i) {
                backward_pointers[i] = std::min(backward_pointers[i], backward_pointers[i + 1]);
            }
        }
        std::cout << cell + 1 << std::endl;
        fflush(stdout);
        if ((c == 1 && backward_pointers[0] == 0) || (c > 1 && forward_pointers.back() >= backward_pointers[0])) {
            return 0;
        }
    }
    return 0;
}
