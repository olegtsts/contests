#include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<bool>> GetFieldFromInput(const int x) {
    std::vector<std::vector<bool>> field(x, std::vector<bool>(x, false));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < x; ++j) {
            char ch;
            std::cin >> ch;
            if (ch == 'X') {
                field[i][j] = true;
            }
        }
    }
    return field;
}

bool CompareFields(const std::vector<std::vector<bool>>& first_field, const std::vector<std::vector<bool>>& second_field) {
    for (size_t i = 0; i < first_field.size(); ++i) {
        for (size_t j = 0; j < second_field.size(); ++j) {
            if (first_field[i][j] != second_field[i][j]) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<bool>> TransposeField(const std::vector<std::vector<bool>>& field) {
    std::vector<std::vector<bool>> new_field(field);
    for (size_t i = 0; i < new_field.size(); ++i) {
        for (size_t j = i + 1; j < new_field.size(); ++j) {
            std::swap(new_field[i][j], new_field[j][i]);
        }
    }
    return new_field;
}

std::vector<std::vector<bool>> ReverseFieldVertically(const std::vector<std::vector<bool>>& field) {
    std::vector<std::vector<bool>> new_field(field);
    for (auto& row: new_field) {
        std::reverse(row.begin(), row.end());
    }
    return new_field;
}

std::vector<std::vector<bool>> RotateField(const std::vector<std::vector<bool>>& field) {
    return ReverseFieldVertically(TransposeField(field));
}

bool CheckFields(const std::vector<std::vector<bool>>& first_field, const std::vector<std::vector<bool>>& second_field) {
    return (
        CompareFields(first_field, second_field)
        || CompareFields(first_field, RotateField(second_field))
        || CompareFields(first_field, RotateField(RotateField(second_field)))
        || CompareFields(first_field, RotateField(RotateField(RotateField(second_field))))
        || CompareFields(ReverseFieldVertically(first_field), second_field)
        || CompareFields(ReverseFieldVertically(first_field), RotateField(second_field))
        || CompareFields(ReverseFieldVertically(first_field), RotateField(RotateField(second_field)))
        || CompareFields(ReverseFieldVertically(first_field), RotateField(RotateField(RotateField(second_field))))
    );
}

int main() {
    int x;
    std::cin >> x;
    auto first_field = GetFieldFromInput(x);
    auto second_field = GetFieldFromInput(x);
    if (CheckFields(first_field, second_field)) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    return 0;
}
