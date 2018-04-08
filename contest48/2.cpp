#include <iostream>
#include <vector>
#include <set>
#include <tuple>

struct Difference {
    long long int difference;
    int index;

    bool operator<(const Difference& other) const {
        return std::forward_as_tuple(difference, index) < std::forward_as_tuple(other.difference, other.index);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    int n,k1,k2;
    std::cin >> n >> k1 >> k2;
    std::vector<long long int> a(n);
    std::vector<long long int> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    std::set<Difference> differences;
    long long int total_difference = 0;
    for (int i = 0; i < n; ++i) {
        long long int local_difference = (a[i] - b[i]) * (a[i] - b[i]);
        differences.insert({local_difference, i});
        total_difference += local_difference;
    }

    int operations_count = k1 + k2;
    while (operations_count > 0) {
        auto diff = *differences.rbegin();
        if (diff.difference == 0) {
            break;
        }
        int i = diff.index;
        if (a[i] > b[i]) {
            ++b[i];
        } else {
            --b[i];
        }
        --operations_count;
        differences.erase(diff);
        long long int local_difference = (a[i] - b[i]) * (a[i] - b[i]);
        differences.insert({local_difference, i});
        total_difference += local_difference - diff.difference;
    }
    std::cout << total_difference + (operations_count % 2) * (operations_count % 2) << std::endl;
    return 0;
}
