#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>
#include <cmath>

std::tuple<int, int> unpack(int index, const int x) {
    int x_count = index % (x + 1);
    index /= (x + 1);
    int s_length = index;
    return std::tie(s_length, x_count);
}

int pack(const int s_length, const int x_count, const int x) {
    int index = 0;
    index += s_length;
    index *= (x + 1);
    index += x_count;
    return index;
}

class SuffixTree {
public:
    SuffixTree(const std::string& s) {
        const int alphabet = 256;
        const int maxlen = std::max(alphabet, static_cast<int>(s.size()));
        const int n = s.size();
        std::vector<int> p(maxlen), cnt(maxlen, 0), c(maxlen);
        for (int i = 0; i < n; ++i) {
            ++cnt[s[i]];
        }
        for (int i = 1; i < alphabet; ++i) {
            cnt[i] += cnt[i-1];
        }
        for (int i = 0; i < n; ++i) {
            p[--cnt[s[i]]] = i;
        }
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[p[i]] != s[p[i - 1]]) {
                ++classes;
            }
            c[p[i]] = classes - 1;
        }
        c_saved.push_back(c);
        std::vector<int> pn(maxlen), cn(maxlen);
        for (int h=0; (1<<h)<n; ++h) {
            for (int i=0; i<n; ++i) {
                pn[i] = p[i] - (1<<h);
                if (pn[i] < 0)  pn[i] += n;
            }
            for (int i = 0; i < classes; ++i) {
                cnt[i] = 0;
            }
            for (int i=0; i<n; ++i)
                ++cnt[c[pn[i]]];
            for (int i=1; i<classes; ++i)
                cnt[i] += cnt[i-1];
            for (int i=n-1; i>=0; --i)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i=1; i<n; ++i) {
                int mid1 = (p[i] + (1<<h)) % n,  mid2 = (p[i-1] + (1<<h)) % n;
                if (c[p[i]] != c[p[i-1]] || c[mid1] != c[mid2])
                    ++classes;
                cn[p[i]] = classes-1;
            }
            std::copy(cn.begin(), cn.begin() + n, c.begin());
            c_saved.push_back(c);
        }
    }
    int get_lcp (int i, int j) {
        int ans = 0;
        for (int k = static_cast<int>(c_saved.size()) - 1; k >= 0; --k) {
            if (c_saved[k][i] == c_saved[k][j]) {
                ans += 1<<k;
                i += 1<<k;
                j += 1<<k;
            }
        }
        return ans;
    }
private:
    std::vector<std::vector<int> > c_saved;
};

class LCPForTwoStrings {
public:
    LCPForTwoStrings(const std::string& s, const std::string& t)
    : suffix_tree(s + "#" + t + "?")
    , s_length(s.size())
    {}

    int get_lcp(const int s_index, const int t_index) {
        return suffix_tree.get_lcp(s_index, t_index + s_length + 1);
    }
private:
    SuffixTree suffix_tree;
    size_t s_length;
};

int main() {
    int a,b;
    std::string s,t;
    std::cin >> a >> s >> b >> t;
    int x;
    std::cin >> x;
    std::vector<int> t_length((s.size() + 1) * (x + 1), 0);
    LCPForTwoStrings lcp_counter(s, t);
    for (size_t i = 0; i < t_length.size(); ++i) {
        if (static_cast<size_t>(t_length[i]) == t.size()) {
            std::cout << "YES\n";
            return 0;
        }
        int s_length, x_count;
        std::tie(s_length, x_count) = unpack(i, x);
        if (static_cast<size_t>(s_length) < s.size()) {
            t_length[pack(s_length + 1, x_count, x)] = std::max(t_length[pack(s_length + 1, x_count, x)],
                    t_length[i]);
        }
        if (x_count < x) {
            int lcp = lcp_counter.get_lcp(s_length, t_length[i]);
            int next_index = pack(s_length + lcp, x_count + 1, x);
            t_length[next_index] = std::max(t_length[i] + lcp, t_length[next_index]);
        }
    }
    std::cout << "NO\n";
    return 0;
}
