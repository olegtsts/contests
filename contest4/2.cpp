#include <iostream>
#include <vector>

long long int get_id(const long long int row, const long long int side, const long long int n) {
    long long int value = (row - 1) * 2 + side - 1;
    if (value >= 0 && value < 2 * n) {
        return value;
    } else {
        return 0;
    }
}

void output_result(
    std::vector<long long int>& vector
) {
    std::cout << vector.size();
    for (auto& id: vector) {
        std::cout << " " << id + 1;
    }
    std::cout << std::endl;
}

int main () {
    long long int n,k;
    std::cin >> n >> k;

    std::vector<long long int> seated(2 * n, 0);

    std::vector<long long int> reds;
    std::vector<long long int> blues;
    std::vector<long long int> blacks;
    std::vector<long long int> yellows;
    std::vector<long long int> pinks;
    long long int min_free_row = 1;
    long long int max_free_row = n;
    for (size_t i = 0; i < k; ++i) {
        long long int row, side;
        std::cin >> row >> side;
        // red
        if (row == min_free_row && (side == 1 || seated[get_id(row, 1, n)] == 1)) {
            reds.push_back(i);
        }

        // blue
        if (row == min_free_row && (side == 2 || seated[get_id(row, 2, n)] == 1)) {
            blues.push_back(i);
        }

        // black
        if (row == max_free_row && (side == 1 || seated[get_id(row, 1, n)] == 1)) {
            blacks.push_back(i);
        }

        // yellows
        if (row == max_free_row && (side == 2|| seated[get_id(row, 2, n)] == 1)) {
            yellows.push_back(i);
        }

        // pink
        pinks.push_back(i);

        seated[get_id(row, side, n)] = 1;
        while (
            min_free_row <= n
            && seated[get_id(min_free_row, 1, n)] == 1 && seated[get_id(min_free_row, 2, n)] == 1
        ) {
            ++min_free_row;
        }

        while (
            max_free_row >= 1
            && seated[get_id(max_free_row, 1, n)] == 1 && seated[get_id(max_free_row, 2, n)] == 1
        ) {
            --max_free_row;
        }
    }

    output_result(reds);
    output_result(blues);
    output_result(blacks);
    output_result(yellows);
    output_result(pinks);

    return 0;
}
