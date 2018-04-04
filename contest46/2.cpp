#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    long long int n,k;
    std::cin >> n >> k;
    std::vector<long long int> a(n);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<bool> t(n);
    for (long long int i = 0; i < n; ++i) {
        long long int flag;
        std::cin >> flag;
        t[i] = (flag > 0);
    }
    long long int lectures_count = 0;
    for (long long int i = 0; i < k; ++i) {
        lectures_count += a[i];
    }
    for (long long int i = k; i < n; ++i) {
        lectures_count += t[i] ? a[i] : 0;
    }
    long long int max_lectures_count = lectures_count;
    for (long long int i = k; i < n; ++i) {
        // get rid of i - k lecture
        lectures_count -= t[i - k] ? 0 : a[i - k];
        // add i-th
        lectures_count += t[i] ? 0 : a[i];
        max_lectures_count = std::max(lectures_count, max_lectures_count);
    }
    std::cout << max_lectures_count << std::endl;
    return 0;
}
