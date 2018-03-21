#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    int ones_count = 0;
    int zeros_count = 0;
    for (auto& symbol : s) {
        if (symbol == '0') {
            ++zeros_count;
        } else {
            ++ones_count;
        }
    }
    if (zeros_count <= ones_count) {
        std::cout << "-1\n";
    } else {
        std::vector<std::vector<int>> target_vectors(zeros_count - ones_count);
        std::set<int> zero_ending_indices;
        std::set<int> one_ending_indices;
        for (int i = 0; i < static_cast<int>(target_vectors.size()); ++i) {
            one_ending_indices.insert(i);
        }
        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            if (s[i] == '1') {
                if (zero_ending_indices.size() == 0) {
                    std::cout << "-1\n";
                    return 0;
                }
                int zero_index = *zero_ending_indices.begin();
                target_vectors[zero_index].push_back(i);
                zero_ending_indices.erase(zero_index);
                one_ending_indices.insert(zero_index);
            } else {
                if (one_ending_indices.size() == 0) {
                    std::cout << "-1\n";
                    return 0;
                }
                int one_index = *one_ending_indices.begin();
                target_vectors[one_index].push_back(i);
                one_ending_indices.erase(one_index);
                zero_ending_indices.insert(one_index);
            }
        }
        std::cout << target_vectors.size() << std::endl;
        for (auto& vect: target_vectors) {
            std::cout << vect.size();
            for (auto& index: vect) {
                std::cout << " " << index + 1;
            }
            std::cout << std::endl;
        }
    }
    return 0;
}
