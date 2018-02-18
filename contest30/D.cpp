#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

struct Segment {
    long long int length = 0;
    int index = 0;

    bool operator<(const Segment& other) const {
        return length < other.length || (length == other.length && index < other.index);
    }
};

struct Triangle {
    Segment first;
    Segment second;
    Segment third;

    int GetMinIndex() const {
        return std::min(std::min(first.index, second.index), third.index);
    }

    friend std::ostream& operator<<(std::ostream& out, const Triangle& triangle) {
        return out << triangle.first.index + 1 << " " << triangle.second.index + 1 << " " << triangle.third.index + 1;
    }
};

class Triangles {
    std::set<Segment> segments;
    std::pair<Triangle, bool> GetPossibleTriangle(const Segment& first, const Segment& second, const Segment& third) {
        if (first.length + second.length > third.length && first.length + third.length > second.length && second.length + third.length > first.length) {
            return {Triangle{first, second, third}, true};
        } else {
            return {{}, false};
        }
    }
public:
    std::pair<Triangle, bool> AddAndFind(const Segment& segment) {
        std::set<Segment>::iterator it = segments.insert(segment).first;
        auto next_it = it;
        ++next_it;
        if (next_it != segments.end()) {
            auto next_next_it = next_it;
            ++next_next_it;
            if (next_next_it != segments.end()) {
                auto possible_trinagle = GetPossibleTriangle(*next_next_it, *next_it, *it);
                if (possible_trinagle.second) {
                    return possible_trinagle;
                }
            }
        }
        if (it != segments.begin()) {
            auto prev_it = it;
            --prev_it;
            if (prev_it != segments.begin()) {
                auto prev_prev_it = prev_it;
                --prev_prev_it;
                auto possible_trinagle = GetPossibleTriangle(*prev_prev_it, *prev_it, *it);
                if (possible_trinagle.second) {
                    return possible_trinagle;
                }
            }
            if (next_it != segments.end()) {
                auto possible_trinagle = GetPossibleTriangle(*prev_it, *it, *next_it);
                if (possible_trinagle.second) {
                    return possible_trinagle;
                }
            }
        }
        return {{}, false};
    }

    void Delete(const Segment& segment) {
        segments.erase(segment);
    }

    std::pair<Triangle, bool> DeleteAndFind(const Segment& segment) {
        segments.erase(segment);
        auto start_search_it = segments.begin();
        if (segments.size() == 0) {
            return {{}, false};
        }
        auto next_it = start_search_it;
        ++next_it;
        if (next_it == segments.end()) {
            return {{}, false};
        }
        auto next_next_it = next_it;
        ++next_next_it;
        std::pair<Triangle, bool> found_triangle({}, false);
        while (next_next_it != segments.end()) {
            auto possible_trinagle = GetPossibleTriangle(*start_search_it, *next_it, *next_next_it);
            if (possible_trinagle.second) {
                if (found_triangle.second == false || found_triangle.first.GetMinIndex() < possible_trinagle.first.GetMinIndex()) {
                    found_triangle = possible_trinagle;
                }
            }
            ++start_search_it;
            ++next_it;
            ++next_next_it;
        }
        return found_triangle;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::pair<Triangle, bool> max_found_triangle({}, false);
    int n,q;
    std::cin >> n >> q;
    std::vector<std::pair<Triangle, bool>> prefix_max_triangles(n + 1, {{}, false});
    int begin_index = 0;
    int last_index = 0;
    Triangles triangles_finder;
    std::vector<Segment> all_segments(n);
    while (last_index < n) {
        Segment& new_segment = all_segments[last_index];
        std::cin >> new_segment.length;
        new_segment.index = last_index++;
        auto possible_trinagle = triangles_finder.AddAndFind(new_segment);
        while (possible_trinagle.second) {
            max_found_triangle = possible_trinagle;
            int new_begin_index = max_found_triangle.first.GetMinIndex();
            for (int i = begin_index; i < new_begin_index; ++i) {
                triangles_finder.Delete(all_segments[i]);
            }
            possible_trinagle = triangles_finder.DeleteAndFind(all_segments[new_begin_index]);
            begin_index = new_begin_index + 1;
        }
        prefix_max_triangles[last_index] = max_found_triangle;
    }
    for (int i = 0; i < q; ++i) {
        int start, finish;
        std::cin >> start >> finish;
        --start;
        --finish;
        auto possible_trinagle = prefix_max_triangles[finish + 1];
        if (possible_trinagle.second && possible_trinagle.first.GetMinIndex() >= start) {
            std::cout << possible_trinagle.first << "\n";
        } else {
            std::cout << "-1\n";
        }
    }
    return 0;
}
