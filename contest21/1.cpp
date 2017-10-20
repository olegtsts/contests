#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n,k,x;
    std::cin >> n >> k >> x;
    int total_time = 0;
    int replaced_counts = 0;
    std::vector<int> a_vector;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        a_vector.push_back(a);
    }
    std::reverse(a_vector.begin(), a_vector.end());
    for (auto& a: a_vector) {
        if (replaced_counts < k) {
            ++replaced_counts;
            total_time += x;
        } else {
            total_time += a;
        }
    }
    std::cout << total_time << std::endl;
    return 0;
}
