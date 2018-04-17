#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class FastPrefixTree {
private:
    struct Node {
        int l, r, par, link;
        std::map<char,int> next;

        Node(int l=0, int r=0, int par=-1)
            : l(l), r(r), par(par), link(-1) {}

        int GetLength()  {  return r - l;  }

        int &GetNextNode (char c) {
            if (!next.count(c))  next[c] = -1;
            return next[c];
        }
    };

    struct State {
        int v, pos;
        State (int v, int pos) : v(v), pos(pos)  {}
    };

    struct LeavesInfo {
        size_t start_index;
        size_t finish_index;
        size_t depth;
    };

    std::string input_string;
    std::vector<Node> nodes;
    size_t nodes_count;
    State ptr;
    std::vector<int> leaves;
    std::vector<LeavesInfo> leaves_info;

public:
    FastPrefixTree(const std::string& input_string_)
        : input_string(input_string_ + '$')
        , nodes(2 * input_string.size())
        , nodes_count(1)
        , ptr(0, 0)
        , leaves()
        , leaves_info()
    {
        for (int i = 0; i < static_cast<int>(input_string.size()); ++i) {
            ExtentTree (i);
        }
        leaves_info.resize(nodes_count);
        UpdateLeavesInfoRecursive(leaves, leaves_info, 0, 0);
    }

    void UpdateLeavesInfoRecursive(
        std::vector<int>& leaves,
        std::vector<LeavesInfo>& leaves_info,
        const int current_node,
        const size_t depth
    ) {
        if (nodes[current_node].next.size() == 0) {
            leaves.push_back(current_node);
            leaves_info[current_node] = {leaves.size() - 1, leaves.size(), depth};
            return;
        }
        size_t start_index = std::numeric_limits<size_t>::max();
        size_t finish_index = 0;
        for (auto& letter_and_child: nodes[current_node].next) {
            auto child = letter_and_child.second;
            UpdateLeavesInfoRecursive(leaves, leaves_info, child, depth + nodes[child].r - nodes[child].l);
            start_index = std::min(start_index, leaves_info[child].start_index);
            finish_index = std::max(finish_index, leaves_info[child].finish_index);
        }
        leaves_info[current_node] = {start_index, finish_index, depth};
    }

    State Go (State st, int l, int r) {
        while (l < r) {
            if (st.pos == nodes[st.v].GetLength()) {
                st = State (nodes[st.v].GetNextNode( input_string[l] ), 0);
                if (st.v == -1)  return st;
            }
            else {
                if (input_string[ nodes[st.v].l + st.pos ] != input_string[l])
                    return State (-1, -1);
                if (r-l < nodes[st.v].GetLength() - st.pos)
                    return State (st.v, st.pos + r-l);
                l += nodes[st.v].GetLength() - st.pos;
                st.pos = nodes[st.v].GetLength();
            }
        }
        return st;
    }

    int Split (State st) {
        if (st.pos == nodes[st.v].GetLength())
            return st.v;
        if (st.pos == 0)
            return nodes[st.v].par;
        Node v = nodes[st.v];
        int id = nodes_count++;
        nodes[id] = Node(v.l, v.l+st.pos, v.par);
        nodes[v.par].GetNextNode( input_string[v.l] ) = id;
        nodes[id].GetNextNode( input_string[v.l+st.pos] ) = st.v;
        nodes[st.v].par = id;
        nodes[st.v].l += st.pos;
        return id;
    }

    int GetLink (int v) {
        if (nodes[v].link != -1)  return nodes[v].link;
        if (nodes[v].par == -1)  return 0;
        int to = GetLink (nodes[v].par);
        return nodes[v].link = Split (Go (State(to,nodes[to].GetLength()), nodes[v].l + (nodes[v].par==0), nodes[v].r));
    }

    void ExtentTree (int pos) {
        while (true) {
            State nptr = Go (ptr, pos, pos+1);
            if (nptr.v != -1) {
                ptr = nptr;
                return;
            }
            int mid = Split (ptr);
            int leaf = nodes_count++;
            nodes[leaf] = Node (pos, input_string.size(), mid);
            nodes[mid].GetNextNode( input_string[pos] ) = leaf;

            ptr.v = GetLink (mid);
            ptr.pos = nodes[ptr.v].GetLength();
            if (!mid)  break;
        }
    }

    std::vector<size_t> GetSortedPositions(const std::string& substring) {
        int current_node = 0;
        size_t scanned = 0;
        while (scanned < substring.size()) {
            char next_symbol = substring[scanned];
            if (nodes[current_node].next.count(next_symbol) == 0) {
                break;
            } else {
                current_node = nodes[current_node].next[next_symbol];
                bool went_wrong = false;
                for (int i = nodes[current_node].l; i < nodes[current_node].r && scanned < substring.size(); ++i) {
                    if (input_string[i] == substring[scanned]) {
                        ++scanned;
                    } else {
                        went_wrong = true;
                        break;
                    }
                }
                if (went_wrong) {
                    break;
                }
            }
        }
        if (scanned == substring.size()) {
            auto& cur_leaves_info = leaves_info[current_node];
            std::vector<size_t> depths;
            for (size_t i = cur_leaves_info.start_index; i < cur_leaves_info.finish_index; ++i) {
                depths.push_back(input_string.size() - leaves_info[leaves[i]].depth);
            }
            std::sort(depths.begin(), depths.end());
            auto last = std::unique(depths.begin(), depths.end());
            depths.erase(last, depths.end());
            return depths;
        } else {
            return {};
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::string input_string;
    std::cin >> input_string;
    FastPrefixTree fast_prefix_tree(input_string);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int number;
        std::string substring;
        std::cin >> number >> substring;
        auto positions = fast_prefix_tree.GetSortedPositions(substring);
        size_t min_distance = std::numeric_limits<size_t>::max();
        for (int j = 0; j + number - 1 < static_cast<int>(positions.size()); ++j) {
            min_distance = std::min(min_distance, positions[j + number - 1] - positions[j] + (substring.size()));
        }
        if (min_distance == std::numeric_limits<size_t>::max()) {
            std::cout << -1 << std::endl;
        } else {
            std::cout << min_distance << std::endl;
        }
    }
    return 0;
}
