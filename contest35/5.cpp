#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void PerformTransformation(std::vector<int>& shifted_positions, const int shift, std::vector<int>& operation_sequence) {
    std::reverse(shifted_positions.begin(), shifted_positions.end());
    std::reverse(shifted_positions.begin() + shift, shifted_positions.end());
    operation_sequence.push_back(shift);
}

int main() {
    int k;
    std::cin >> k;
    std::string s,t;
    std::cin >> s >> t;
    std::vector<std::vector<int>> letter_indices('z' - 'a' + 1);
    for (size_t i = 0; i < t.size(); ++i) {
        letter_indices[t[i] - 'a'].push_back(i);
    }
    std::vector<int> shifted_positions(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        if (letter_indices[s[i] - 'a'].size() > 0) {
            shifted_positions[i] = letter_indices[s[i] - 'a'].back();
            letter_indices[s[i] - 'a'].pop_back();
        } else {
            std::cout << -1 << std::endl;
            return 0;
        }
    }
    std::vector<int> operation_sequence;
    for (size_t i = 0; i < s.size(); ++i) {
        int ith_position = 0;
        for (size_t j = 0; j < s.size(); ++j) {
            if (shifted_positions[j] == static_cast<int>(i)) {
                ith_position = j;
                break;
            }
        }
        PerformTransformation(shifted_positions, static_cast<int>(s.size()) - ith_position - 1, operation_sequence);
        PerformTransformation(shifted_positions, 1, operation_sequence);
        PerformTransformation(shifted_positions, static_cast<int>(s.size()), operation_sequence);
    }
    std::cout << operation_sequence.size() << std::endl;
    for (size_t i = 0; i < operation_sequence.size(); ++i) {
        std::cout << operation_sequence[i];
        if (i + 1 < operation_sequence.size()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}
