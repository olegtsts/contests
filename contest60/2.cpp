#include <set>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

class DanceSquare {
public:
    DanceSquare(int rows, int cols)
        : bad_dancers(),
          rows(rows),
          cols(cols),
          interest(0),
          rows_dancers(rows),
          cols_dancers(cols),
          dancers(rows, std::vector<long long int>(cols, 0))
    {
    }

    std::vector<int> GetNeighboursInSet(const std::set<int>& input_set, int element) {
        std::vector<int> res;
        auto it = input_set.upper_bound(element);
        if (it != input_set.end()) {
            res.push_back(*it);
        }
        auto it2 = input_set.lower_bound(element);
        if (it2 != input_set.begin()) {
            --it2;
            res.push_back(*it2);
        }
        return res;
    }

    std::vector<std::pair<int, int>> GetNeibours(int row, int col) {
        std::vector<std::pair<int, int>> pairs;
        for (int other_col : GetNeighboursInSet(rows_dancers[row], col)) {
            pairs.push_back(std::make_pair(row, other_col));
        }
        for (int other_row : GetNeighboursInSet(cols_dancers[col], row)) {
            pairs.push_back(std::make_pair(other_row, col));
        }
        return pairs;
    }

    void UpdateDancer(int row, int col) {
        long long int compas_count = 0;
        long long int compas_skill = 0;
        for (auto one_pair : GetNeibours(row, col)) {
            compas_skill += dancers[one_pair.first][one_pair.second];
            compas_count += 1ll;
        }
        if (dancers[row][col] * compas_count < compas_skill) {
            bad_dancers.insert(std::make_pair(row, col));
        } else {
            bad_dancers.erase(std::make_pair(row, col));
        }
    }

    void AddDancer(int row, int col, long long int skill) {
        interest += skill;
        rows_dancers[row].insert(col);
        cols_dancers[col].insert(row);
        dancers[row][col] = skill;
        UpdateDancer(row, col);
        for (auto one_pair : GetNeibours(row, col)) {
            UpdateDancer(one_pair.first, one_pair.second);
        }
    }

    void RemoveDancer(int row, int col) {
        interest -= dancers[row][col];
        rows_dancers[row].erase(col);
        cols_dancers[col].erase(row);
        bad_dancers.erase(std::make_pair(row, col));
        for (auto one_pair: GetNeibours(row, col)) {
            UpdateDancer(one_pair.first, one_pair.second);
        }
    }

    long long int GetInterest() const {
        return interest;
    }

    std::set<std::pair<int, int>> GetBadDancers() const {
        return bad_dancers;
    }
private:
    std::set<std::pair<int, int>> bad_dancers;
    int rows;
    int cols;
    long long int interest;
    std::vector<std::set<int>> rows_dancers;
    std::vector<std::set<int>> cols_dancers;
    std::vector<std::vector<long long int>> dancers;
};

long long int ProcessTest() {
    int rows;
    int cols;
    std::cin >> rows >> cols;
    DanceSquare dance_square(rows, cols);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            long long int skill;
            std::cin >> skill;
            dance_square.AddDancer(row, col, skill);
        }
    }
    long long int interest = 0;
    while (1) {
        interest += dance_square.GetInterest();
        auto bad_dancers = dance_square.GetBadDancers();
        if (bad_dancers.size() == 0) {
            break;
        }
        for (auto one_pair : bad_dancers) {
            dance_square.RemoveDancer(one_pair.first, one_pair.second);
        }
    }
    return interest;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ": " << ProcessTest() << std::endl;
    }
    return 0;
}
