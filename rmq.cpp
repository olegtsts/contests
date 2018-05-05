#include <iostream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cassert>
#include <stack>


template
<typename T>
class SimpleRMQ {
public:
    SimpleRMQ(const std::vector<T>& vect)
        : mins({std::vector<size_t>(vect.size())})
        , data(vect)
    {
        for (size_t i = 0; i < vect.size(); ++i) {
            mins[0][i] = i;
        }

        while (mins.back().size()) {
            std::vector<size_t> next;
            size_t prev_size = (1 << (mins.size() - 1));
            for (size_t i = 0; i + prev_size < mins.back().size(); ++i) {
                if (vect[mins.back()[i]] < vect[mins.back()[i + prev_size]]) {
                    next.push_back(mins.back()[i]);
                } else {
                    next.push_back(mins.back()[i + prev_size]);
                }
            }
            mins.emplace_back(std::move(next));
        }
    }

    size_t GetMinIndex(const size_t from, size_t to) const {
        to = std::min(data.size(), to);
        if (from >= to) {
            throw std::runtime_error("from >= to");
        }
        size_t pow = 0;
        while ((1 << pow) <= to - from) {
            ++pow;
        }
        --pow;
        if (data[mins[pow][from]] < data[mins[pow][to - (1 << pow)]]) {
            return mins[pow][from];
        } else {
            return mins[pow][to - (1 << pow)];
        }
    }

private:
    std::vector<std::vector<size_t>> mins;
    std::vector<T> data;
};

size_t ComputeSize(const size_t size) {
    return std::ceil(log(std::ceil(sqrt(static_cast<double>(size)))));
}

class RestrictedRMQ {
private:
    std::unordered_map<int, std::shared_ptr<SimpleRMQ<int>>> BuildRMQs() {
        std::unordered_map<int, std::shared_ptr<SimpleRMQ<int>>> rmqs;

        for (size_t i = 0; i < data.size(); i+=size) {
            int hash = 0;
            for (size_t j = 1; j < size && i + j < data.size(); ++j) {
                if (i + j < data.size() && data[i + j - 1] > data[i + j]) {
                    hash |= 1;
                }
                hash <<= 1;
            }
            if (rmqs.count(hash) == 0) {
                rmqs[hash] = std::make_shared<SimpleRMQ<int>>(std::vector<int>(data.begin() + i, data.begin() + std::min(i + size, data.size())));
            }
            hash_mapping[i / size] = hash;
        }
        return rmqs;
    }

    size_t SizeRounUp(const size_t val) const {
        if (val % size == 0) {
            return val;
        } else {
            return val + size - val % size;
        }
    }

    size_t ProcessSmallSegment(const size_t from, const size_t to) const {
        int hash = hash_mapping[from / size];
        return rmqs.at(hash)->GetMinIndex(from % size, to % size == 0 ? size : to % size);
    }

    std::vector<int> BuildRMQBase() {
        std::vector<int> base;

        for (size_t i = 0; i < data.size(); i+=size) {
            base.push_back(data[rmqs[hash_mapping[i / size]]->GetMinIndex(0, size) + i]);
        }
        return base;
    }

public:
    RestrictedRMQ(const std::vector<int>& vect)
        : data(vect)
        , size(ComputeSize(vect.size()))
        , hash_mapping((vect.size() + size - 1) / size)
        , rmqs(BuildRMQs())
        , total_rmq(BuildRMQBase())
    {}

    size_t GetMinIndex(const size_t from, const size_t to) const {
        if (from >= to) {
            throw std::runtime_error("from >= to");
        }

        std::vector<size_t> indexes;
        size_t f = SizeRounUp(from);
        size_t t = to - to % size;


        if (from < f && f <= to) {
            indexes.push_back(ProcessSmallSegment(from, f) + f - size);
        }

        if (from <= f && f < t && t <= to) {
            size_t segment_index = (total_rmq.GetMinIndex(f / size, t / size));
            indexes.push_back(ProcessSmallSegment(segment_index * size, segment_index * size + size) + segment_index * size);
        }

        if (from <= t && t < to) {
            indexes.push_back(ProcessSmallSegment(t, to) + t);
        }

        if (t <= from && from < to && to <= f) {
            indexes.push_back(ProcessSmallSegment(from, to) + f - size);
        }
        assert(indexes.size());
        size_t min_index = indexes[0];
        for (size_t i: indexes) {
            if (data[min_index] > data[i]) {
                min_index = i;
            }
        }

        return min_index;
    }


private:
    std::vector<int> data;
    size_t size;
    std::vector<int> hash_mapping;
    std::unordered_map<int, std::shared_ptr<SimpleRMQ<int>>> rmqs;
    SimpleRMQ<int> total_rmq;
};


struct TreeNode {
    static size_t None;

    size_t left = None;
    size_t right = None;
};

size_t TreeNode::None(-1);

struct Tree {
    std::vector<TreeNode> tree;
    size_t root;
};



class LCA {
private:
    void AddToPath(const size_t node, const size_t dep, std::vector<int>& path) {
        tree_to_rmq[node] = path.size();
        path.push_back(dep);
        rmq_to_tree.push_back(node);
    }

    void EulerianPathRec(const size_t node, const std::vector<TreeNode>& tree, std::vector<int>& path, const size_t dep) {
        AddToPath(node, dep, path);
        if (tree[node].left != TreeNode::None) {
            EulerianPathRec(tree[node].left, tree, path, dep + 1);
            AddToPath(node, dep, path);
        }

        if (tree[node].right != TreeNode::None) {
            EulerianPathRec(tree[node].right, tree, path, dep + 1);
            AddToPath(node, dep, path);
        }
    }

    std::vector<int> EulerianPath(const Tree& tree)  {
        std::vector<int> path;
        EulerianPathRec(tree.root, tree.tree, path, 0);
        return path;
    }

public:
    LCA(const Tree& tree)
        : tree_to_rmq(tree.tree.size(), 0)
        , rmq_to_tree()
        , rmq(EulerianPath(tree))
    {}

    size_t GetLCA(const size_t first, const size_t second) const {
        size_t f_rmq = tree_to_rmq[first];
        size_t s_rmq = tree_to_rmq[second];
        if (f_rmq > s_rmq) {
            std::swap(f_rmq, s_rmq);
        }

        return rmq_to_tree[rmq.GetMinIndex(f_rmq, s_rmq + 1)];
    }



private:
    std::vector<size_t> tree_to_rmq;
    std::vector<size_t> rmq_to_tree;
    RestrictedRMQ rmq;
};

template
<typename T>
class RMQ {
private:
    Tree BuildTree(const std::vector<int>& data) const {
        std::vector<TreeNode> tree(data.size());
        std::stack<size_t> s;

        for (size_t i = 0; i < data.size(); ++i) {
            size_t last_popped = TreeNode::None;
            while (s.size() && data[s.top()] > data[i]) {
                last_popped = s.top();
                s.pop();
            }

            // data[s.top()] < data[i] < data[last_popped]
            // s.top() ... last_pophed .. i
            if (last_popped != TreeNode::None) {
                tree[i].left = last_popped;
            }

            if (s.size()) {
                tree[s.top()].right = i;
            }

            s.push(i);
        }

        size_t root = s.top();
        while (s.size()) {
            root = s.top();
            s.pop();
        }
        return {tree, root};
    }
public:
    RMQ(const std::vector<int>& data)
        : lca(BuildTree(data))
    {}

    size_t GetMinIndex(const size_t from, const size_t to) const {
        return lca.GetLCA(from, to - 1);
    }

private:
    LCA lca;
};

int main() {
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<int> testing_array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> testing_array[i];
    }
    RMQ<int> rmq(testing_array);
    for (int i = 0; i < m; ++i) {
        int start,finish;
        std::cin >> start >> finish;
        std::cout << rmq.GetMinIndex(start, finish) << std::endl;
    }
    return 0;
}

