#include <algorithm>
#include <iostream>
#include <vector>

long long int GetResult(std::vector<int>::iterator cur_begin, std::vector<int>::iterator cur_end) {
    std::cout << "? " << cur_end - cur_begin;
    std::for_each(cur_begin, cur_end, [](const int element) {std::cout << " " << element;});
    std::cout << std::endl;
    long long int input;
    std::cin >> input;
    return input;
}

int main() {
    int n;
    long long int x,y;
    std::cin >> n >> x >> y;
    long long int z = x ^ y;
    std::vector<std::vector<int>> sets(11);
    for (int i = 0; i < 10; ++i) {
        for (int j = 1; j <= n; ++j) {
            if ((j & (1 << i)) > 0) {
                sets[i].push_back(j);
            }
        }
    }
    std::vector<bool> one_bit_results(11);
    int one_of_bits;
    for (int i = 0; i < 10; ++i) {
        if (sets[i].size() > 0) {
            long long int input = GetResult(sets[i].begin(), sets[i].end());
            one_bit_results[i] = (input == y || input == z);
        } else {
            one_bit_results[i] = false;
        }
        if (one_bit_results[i]) {
            one_of_bits = i;
        }
    }

    std::vector<std::vector<int>> new_sets(11);

    for (int i = 0; i < 10; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (((j & (1 << i)) > 0) && ((j & (1 << one_of_bits)) > 0)) {
                new_sets[i].push_back(j);
            }
        }
    }

    std::vector<bool> new_results(11);
    for (int i = 0; i < 10; ++i) {
        if (new_sets[i].size() > 0 && i != one_of_bits) {
            long long int input = GetResult(new_sets[i].begin(), new_sets[i].end());
            new_results[i] = (input == y || input == z);
        } else if (i == one_of_bits) {
            new_results[i] = true;
        } else {
            new_results[i] = false;
        }
    }
    int first_index = 0;
    int second_index = (1 << one_of_bits);

    for (int i = 0; i < 10; ++i) {
        if (i != one_of_bits) {
            if (new_results[i]) {
                second_index ^= (1 << i);
            }
            if (!(new_results[i] ^ one_bit_results[one_of_bits] ^ one_bit_results[i])) {
                first_index ^= (1 << i);
            }
        }
    }
    std::cout << "! " << first_index << " " << second_index << std::endl;
    return 0;
}
