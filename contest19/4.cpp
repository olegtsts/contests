#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <climits>

int main() {
    int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<std::tuple<int, int, long long int>> incoming;
    std::vector<std::tuple<int, int, long long int>> outgoing;
    incoming.reserve(m);
    outgoing.reserve(m);
    for (int i = 0; i < m; ++i) {
        int d, f, t;
        long long int c;
        std::cin >> d >> f >> t >> c;
        --d;
        if (t == 0) {
            --f;
            incoming.push_back(std::make_tuple(d, f, c));
        } else {
            --t;
            outgoing.push_back(std::make_tuple(d, t, c));
        }
    }
    const int max_day = 1000000;
    const long long int max_cost = 1000001;
    std::sort(incoming.begin(), incoming.end());
    std::sort(outgoing.begin(), outgoing.end(), [] (const auto a, const auto b) {return a > b;});
    std::vector<long long int> less_equal_cost(max_day, LLONG_MAX);
    std::vector<long long int> more_equal_cost(max_day, LLONG_MAX);
    std::vector<long long int> city_cost(n, max_cost);
    long long int sum_cost = max_cost * n;
    int min_possible_value = max_day + 1;
    int possible_counter = n;
    int prev_day = 0;
    for (auto& cur_tuple: incoming) {
        int d, f;
        long long int c;
        std::tie(d, f, c) = cur_tuple;
        sum_cost -= city_cost[f];
        if (city_cost[f] == max_cost) {
            --possible_counter;
            if (possible_counter == 0) {
                min_possible_value = d;
            }
        }
        city_cost[f] = std::min(city_cost[f], c);
        sum_cost += city_cost[f];
        while (prev_day < d) {
            less_equal_cost[prev_day + 1] = less_equal_cost[prev_day];
            ++prev_day;
        }
        less_equal_cost[prev_day] = sum_cost;
    }
    while (prev_day + 1 < max_day) {
        less_equal_cost[prev_day + 1] = less_equal_cost[prev_day];
        ++prev_day;
    }
    city_cost.assign(n, max_cost);
    sum_cost = max_cost * n;
    possible_counter = n;
    int max_possible_value = -1;
    prev_day = max_day - 1;
    for (auto& cur_tuple: outgoing) {
        int d, t;
        long long int c;
        std::tie(d, t, c) = cur_tuple;
        sum_cost -= city_cost[t];
        if (city_cost[t] == max_cost) {
            --possible_counter;
            if (possible_counter == 0) {
                max_possible_value = d;
            }
        }
        city_cost[t] = std::min(city_cost[t], c);
        sum_cost += city_cost[t];
        while (prev_day > d) {
            more_equal_cost[prev_day - 1] = more_equal_cost[prev_day];
            --prev_day;
        }
        more_equal_cost[prev_day] = sum_cost;
    }
    while (prev_day > 0) {
        more_equal_cost[prev_day - 1] = more_equal_cost[prev_day];
        --prev_day;
    }
    long long int result = LLONG_MAX;
    for (int i = 0; i + k + 1 < max_day; ++i) {
        if (
            result > less_equal_cost[i] + more_equal_cost[i + k + 1]
            && i >= min_possible_value
            && i + k + 1 <= max_possible_value
        ) {
            result = less_equal_cost[i] + more_equal_cost[i + k + 1];
        }
    }
    if (result == LLONG_MAX) {
        result = -1;
    }
    std::cout << result << std::endl;
    return 0;
}
