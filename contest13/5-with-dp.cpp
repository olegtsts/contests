#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

std::tuple<int, int, bool> unpack(int index, const int x) {
    int s_length;
    int subwords;
    bool is_last_used;
    is_last_used = index % 2;
    index -= is_last_used ? 1 : 0;
    index /= 2;
    subwords = index % (x + 1);
    index /= (x + 1);
    s_length = index;
    return std::make_tuple(s_length, subwords, is_last_used);
}

int pack(int s_length, int subwords, bool is_last_used, const int x) {
    int index = 0;
    index += s_length;
    index *= (x + 1);
    index += subwords;
    index *= 2;
    index += is_last_used ? 1 : 0;
    return index;
}

int main() {
    int a,b;
    std::string s,t;
    std::cin >> a >> s >> b >> t;
    int x;
    std::cin >> x;
    std::vector<int> max_t_prefix((s.size() + 1) * (x + 1) * 2, 0);
    for (size_t i = 0; i < max_t_prefix.size(); ++i) {
        int s_length, subwords;
        bool is_last_used;
        std::tie(s_length, subwords, is_last_used) = unpack(i, x);
//        std::cout << "Counting s_length " << s_length << " subwords " << subwords << std::boolalpha << " is_last_used " << is_last_used;
        if (s_length == 0 || subwords == 0) {
            max_t_prefix[i] = 0;
        } else if (is_last_used) {
            for (auto& t_length: {
                    max_t_prefix[pack(s_length - 1, subwords, true, x)],
                    max_t_prefix[pack(s_length - 1, subwords - 1, false, x)]}) {
                if (static_cast<size_t>(t_length) < t.size() && t[t_length] == s[s_length - 1] && max_t_prefix[i] < t_length + 1) {
                    max_t_prefix[i] = t_length + 1;
                }
            }
        } else {
            max_t_prefix[i] = std::max(max_t_prefix[pack(s_length - 1, subwords, false, x)],
                    max_t_prefix[pack(s_length - 1, subwords, true, x)]);
        }
//        std::cout << " done counting " << max_t_prefix[i] << "\n";
        if (static_cast<size_t>(max_t_prefix[i]) == t.size()) {
            std::cout << "YES\n";
            return 0;
        }
    }
    std::cout << "NO\n";
    return 0;
}
