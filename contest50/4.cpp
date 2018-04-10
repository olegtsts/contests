#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <map>

int main() {
    int n;
    std::cin >> n;
    std::vector<long long int> a(n);
    std::map<long long int, std::set<int>> number_positions;
    for (int i = 0; i < n; ++i){
        long long int number;
        std::cin >> number;
        if (number_positions.count(number) == 0) {
            number_positions[number] = {};
        }
        number_positions[number].insert(i);
    }
    std::vector<std::pair<int, long long int>> positions_and_numbers;
    while (number_positions.size() > 0) {
        auto first_element = number_positions.begin();
        long long int number = first_element->first;
        std::set<int>& positions = first_element->second;
        if (positions.size() == 1) {
            positions_and_numbers.push_back({*positions.begin(), number});
            number_positions.erase(number);
        } else if (positions.size() > 1) {
            int first_position = *positions.begin();
            positions.erase(first_position);
            int second_position = *positions.begin();
            positions.erase(second_position);
            if (positions.size() == 0) {
                number_positions.erase(number);
            }
            if (number_positions.count(2 * number) == 0) {
                number_positions[2 * number] = {};
            }
            number_positions[2 * number].insert(second_position);
        }
    }
    std::sort(positions_and_numbers.begin(), positions_and_numbers.end());
    std::cout << positions_and_numbers.size() << std::endl;
    for (auto& pair: positions_and_numbers) {
        std::cout << pair.second << " ";
    }
    return 0;
}
