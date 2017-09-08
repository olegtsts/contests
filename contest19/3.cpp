#include <set>
#include <utility>
#include <iostream>
#include <vector>

int main() {
    std::set<std::pair<long long int, int>> delay_index;
    int n, k;
    std::cin >> n >> k;
    std::vector<int> sorted_indexes(n);
    long long int sum_cost = 0;
    int new_position = k + 1;
    for (int i = 0; i < n; ++i) {
        long long int delay;
        std::cin >> delay;
        delay_index.insert(std::make_pair(delay, i));
        if (static_cast<int>(delay_index.size()) > k) {
            auto cur_pair_it = delay_index.end();
            --cur_pair_it;
            sorted_indexes[cur_pair_it->second] = new_position;
            sum_cost += (new_position - cur_pair_it->second - 1) * cur_pair_it->first;
            ++new_position;
            delay_index.erase(*cur_pair_it);
        }
    }
    while (delay_index.size() > 0) {
        auto cur_pair_it = delay_index.end();
        --cur_pair_it;
        sorted_indexes[cur_pair_it->second] = new_position;
        sum_cost += (new_position - cur_pair_it->second - 1) * cur_pair_it->first;
        ++new_position;
        delay_index.erase(*cur_pair_it);
    }
    std::cout << sum_cost << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << sorted_indexes[i];
        if (i + 1 < n) {
            std::cout << " ";
        }
    }
    return 0;
}
