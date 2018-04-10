#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<long long int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    long long int sum_of_tasks = 0;
    for (int i = 0; i < n; ++i) {
        sum_of_tasks += a[i];
    }
    long long int current_sum = 0;
    for (int i = 0; i < n; ++i) {
        current_sum += a[i];
        if (current_sum >= (sum_of_tasks + 1) / 2) {
            std::cout << i + 1 << std::endl;
            break;
        }
    }
    return 0;
}
