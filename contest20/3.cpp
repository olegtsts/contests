#include <iostream>
#include <algorithm>

int main() {
    long long int f,a,b,k;
    std::cin >> a >> b >> f >> k;
    if (f > b) {
        std::cout << "-1\n";
        return 0;
    }
    long long int distance_to_next = 2 * (a - f);
    long long int gas_remained = b;
    long long int path_remained = a * k;
    path_remained -= f;
    gas_remained -= f;
    int change_counts = 0;
    while (path_remained > 0) {
        long long int need_path = std::min(distance_to_next, path_remained);
        if (gas_remained < need_path) {
            gas_remained = b;
            ++change_counts;
        }
        if (gas_remained < need_path) {
            std::cout << "-1\n";
            return 0;
        }
        gas_remained -= need_path;
        path_remained -= need_path;
        distance_to_next = 2 * a - distance_to_next;
    }

    std::cout << change_counts << std::endl;
    return 0;
}
