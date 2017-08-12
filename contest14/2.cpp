#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

bool are_all_zeros(
        const int k,
        std::vector<int>& a
) {
    for (int i = 0; i < k; ++i) {
        if (a[i] != 0) {
            return false;
        }
    }
    return true;
}


bool is_possible_only_quarters(
        const int k,
        std::vector<int>& a,
        int quarter_count
) {
    for (int i = 0; i < k; ++i) {
        if (a[i] % 4 == 3 && quarter_count > 0) {
            --quarter_count;
            a[i] -= 3;
        }
    }
    if (quarter_count == 0) {
        return are_all_zeros(k, a);
    }

    // quarter_count > 0 && no 3 remainders, only 0, 1, 2

    for (int i = 0; i < k; ++i) {
        if (a[i] % 4 == 0 && quarter_count > 0) {
            int rows = std::min(quarter_count, a[i] / 4);
            quarter_count -= rows;
            a[i] -= 4 * rows;
        }
    }
    if (quarter_count == 0) {
        return are_all_zeros(k, a);
    }
    // quarter_count > 0 && only 1,2 remainders, rest are zeros

    std::deque<int> one_remainders;
    std::deque<int> two_remainders;
    for (int i = 0; i < k; ++i) {
        if (a[i] % 4 == 1) {
            one_remainders.push_back(a[i]);
        } else if (a[i] % 4 == 2) {
            two_remainders.push_back(a[i]);
        }
    }
    while (one_remainders.size() > 0 && two_remainders.size() > 0 && quarter_count > 0) {
        int one_num = *(one_remainders.begin());
        int second_num = *(two_remainders.begin());
        int rows = (one_num + second_num + 1) / 4;
        if (rows > quarter_count) {
            return false;
        }
        quarter_count -= rows;
        one_remainders.pop_front();
        two_remainders.pop_front();
    }
    if (quarter_count == 0) {
        return are_all_zeros(k, a);
    }
    // quarter_count >=0 , either one _remainders or two_remainders are empty

    while (one_remainders.size() >= 2) {
        auto it = one_remainders.begin();
        int first_num = *it++;
        int second_num = *it++;
        int rows = (first_num + second_num + 2) / 4;
        if (rows > quarter_count) {
            return false;
        }
        quarter_count -= rows;
        one_remainders.pop_front();
        one_remainders.pop_front();
    }
    if (one_remainders.size() == 1) {
        int first_num = *(one_remainders.begin());
        return quarter_count >= (first_num + 3) / 4;
    }
    while (two_remainders.size() >= 3) {
        auto it = two_remainders.begin();
        int first_num = *it++;
        int second_num = *it++;
        int third_num = *it++;
        int rows = (first_num + second_num + third_num + 2) / 4;
        if (rows > quarter_count) {
            return false;
        }
        quarter_count -= rows;
        two_remainders.pop_front();
        two_remainders.pop_front();
        two_remainders.pop_front();
    }
    if (two_remainders.size() == 1) {
        int first_num = *(two_remainders.begin());
        return quarter_count >= (first_num + 2) / 4;
    } else if (two_remainders.size() == 2) {
        auto it = two_remainders.begin();
        int first_num = *it++;
        int second_num = *it++;
        return quarter_count >= (first_num + second_num + 4) / 4;
    }

    // one_remainders and two_remainders are empty
    return true;
}

bool is_possible_only_doubles(
        const int k,
        std::vector<int>& a,
        int double_count
) {
    for (int i = 0; i < k; ++i) {
        int how_much_needed = (a[i] + 1) / 2;
        double_count -= how_much_needed;
    }
    return (double_count >= 0);
}

bool is_possible(
        const int k,
        std::vector<int>& a,
        int double_count,
        int quarter_count
) {
    for (int i = 0; i < k; ++i) {
        if (a[i] % 2 == 1 && double_count > 0) {
            --double_count;
            --a[i];
        }
    }
    if (double_count == 0) {
        return is_possible_only_quarters(k, a, quarter_count);
    }
    // double_count > 0 and all a[i] are even

    for (int i = 0; i < k; ++i) {
        if (a[i] % 4 == 2 && double_count > 0) {
            --double_count;
            a[i] -= 2;
        }
    }
    if (double_count == 0) {
        return is_possible_only_quarters(k, a, quarter_count);
    }
    // double_count > 0 and all a[i] div by 4

    for (int i = 0; i < k; ++i) {
        if (a[i] >= 4 && quarter_count > 0) {
            int rows = std::min(a[i] / 4, quarter_count);
            a[i] -= 4 * rows;
            quarter_count -= rows;
        }
    }

    if (quarter_count == 0) {
        return is_possible_only_doubles(k, a, double_count);
    }

    // quarter_count > 0 and all a[i] = 0
    return true;
}

int main() {
    int n,k;
    std::cin >> n >> k;
    std::vector<int> a(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> a[i];
    }
    if (is_possible(k, a, 2 * n, n)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    return 0;
}
