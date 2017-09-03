#include <iostream>
#include <string>
#include <vector>
#include <tuple>

int get_symmetric(const int segment_begin, const int segment_end, const int point) {
    return segment_end - 1 - point + segment_begin;
}

int get_begin(int center, int size) {
    if (center % 2 == 0) {
        return center / 2 - size / 2;
    } else {
        return center / 2 - size / 2;
    }
}

int get_end(int center, int size) {
    return get_begin(center, size) + size;
}

std::tuple<int, int> get_begin_end(int center, int k) {
    return std::make_tuple(get_begin(center, k + 1), get_end(center, k + 1));
}

std::tuple<int, int> get_center_and_length(int substring_begin, int substring_end) {
    return std::make_tuple(substring_begin + substring_end, substring_end - substring_begin - 1);
}

int main() {
    std::string s;
    std::cin >> s;
    std::vector<int> degrees(2 * s.size() * s.size(), 0);
    int max_polyndrom_begin = 0;
    int max_polyndrom_end = 0;
    int string_length = static_cast<int>(s.size());
    for (int i = 0; i < 2 * string_length; ++i) {
        int k = i % 2 == 0 ? 1 : 0;
        bool zero_at_the_end = false;
        if (i > max_polyndrom_begin + max_polyndrom_end) {
            int prev_index = 2 * (max_polyndrom_end + max_polyndrom_begin) - i;
            while (k < string_length) {
                int cur_begin, cur_end;
                std::tie(cur_begin, cur_end) = get_begin_end(i, k);
                if (cur_end <= max_polyndrom_end && cur_begin >= max_polyndrom_begin) {
                    degrees[i * string_length + k] = degrees[prev_index * string_length + k];
                    if (degrees[i * string_length + k] == 0) {
                        zero_at_the_end = true;
                    }
                } else {
                    break;
                }
                k += 2;
            }
        }
        if (!zero_at_the_end) {
            while (k < string_length) {
                int cur_begin, cur_end;
                std::tie(cur_begin, cur_end) = get_begin_end(i, k);
                if (cur_begin >= 0 && cur_end <= string_length && s[cur_begin] == s[cur_end - 1]) {
                    int middle = (cur_end + cur_begin) / 2;
                    int prev_index, prev_k;
                    if (middle > cur_begin) {
                        std::tie(prev_index, prev_k) = get_center_and_length(cur_begin, middle);
                        degrees[i * string_length + k] = degrees[prev_index * string_length + prev_k] + 1;
                    } else {
                        degrees[i * string_length + k] = 1;
                    }
                    if (cur_end > max_polyndrom_end) {
                        max_polyndrom_end = cur_end;
                        max_polyndrom_begin = cur_begin;
                    }
                } else {
                    break;
                }
                k += 2;
            }
        }
    }

    std::vector<int> result(s.size() + 1, 0);
    for (size_t i = 0; i < 2 * s.size(); ++i) {
        for (size_t k = 0; k < s.size(); ++k) {
            for (int j = 0; j <= degrees[i * s.size() + k]; ++j) {
                ++result[j];
            }
        }
    }

    for (size_t k = 1; k <= s.size(); ++k) {
        std::cout << result[k];
        if (k + 1 <= s.size()) {
            std::cout << " ";
        }
    }
    return 0;
}
