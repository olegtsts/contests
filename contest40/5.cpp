#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

std::tuple<std::vector<int>, std::vector<int>> GetCountsAndLastIndices(const std::string& input_string) {
    std::vector<int> counts(input_string.size() + 1, 0);
    std::vector<int> last_indices(input_string.size() + 1, -1);
    for (int i = 0; i < static_cast<int>(input_string.size()); ++i) {
        counts[i + 1] = counts[i] + (input_string[i] != 'A');
        last_indices[i + 1] = last_indices[i];
        if (input_string[i] != 'A') {
            last_indices[i + 1] = i;
        }
    }
    return std::make_tuple(counts, last_indices);
}

int main() {
    std::string s;
    std::string t;
    std::cin >> s;
    std::cin >> t;
    std::vector<int> s_counts;
    std::vector<int> t_counts;
    std::vector<int> t_last_indices;
    std::vector<int> s_last_indices;
    std::tie(s_counts, s_last_indices) = GetCountsAndLastIndices(s);
    std::tie(t_counts, t_last_indices) = GetCountsAndLastIndices(t);
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int a,b,c,d;
        std::cin >> a >> b >> c >> d;
        --a;
        --c;
        int s_count = s_counts[b] - s_counts[a];
        int t_count = t_counts[d] - t_counts[c];
        int last_s_count = b - std::max(a, s_last_indices[b]);
        int last_t_count = d - std::max(c, t_last_indices[d]);
        if ((s_count + t_count) % 2 == 0 && ((s_count == t_count && last_s_count >= last_t_count && (last_s_count - last_t_count) % 3 == 0)
                                             || (s_count < t_count && last_s_count >= last_t_count))) {
            std::cout << "1";
        } else {
            std::cout << "0";
        }
    }
    std::cout << std::endl;
    return 0;
}
