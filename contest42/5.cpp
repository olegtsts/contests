#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>

struct Box {
    bool is_important = false;
    int size;
};

struct LevelReachability {
    bool is_reachable = false;
    int how_much_important_waisted = 0;

    bool operator<(const LevelReachability& other) const {
        return std::forward_as_tuple(is_reachable, -how_much_important_waisted)
            < std::forward_as_tuple(other.is_reachable, -other.how_much_important_waisted);
    }
};

struct MinReachabilityLevels {
    int min_reachable_level_after_l = -1;
    int min_reachable_level_after_l_without_one_important = -1;
};

int main() {
    int n;
    int l,r;
    std::cin >> n >> l >> r;
    std::vector<Box> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].size;
    }
    for (int i = 0; i < n; ++i) {
        int is_important;
        std::cin >> is_important;
        a[i].is_important = static_cast<bool>(is_important);
    }
    std::sort(a.begin(), a.end(), [](const Box& first, const Box& second) {
        return std::forward_as_tuple(first.is_important, -first.size) < std::forward_as_tuple(second.is_important, -second.size);
    });
    std::vector<LevelReachability> level_reachability(10001, {false, 0});
    level_reachability[0] = {true, 0};
    std::vector<MinReachabilityLevels> boxes_count_min_reachability_levels(n + 1, MinReachabilityLevels{-1, -1});
    int important_boxes = 0;
    for (int i = 0; i < n; ++i) {
        std::vector<LevelReachability> new_level_reachability(10001, {false, 0});
        Box new_box = a[i];
        if (new_box.is_important) {
            important_boxes += 1;
        }
        for (int level = 0; level <= 10000; ++level) {
            new_level_reachability[level] = std::max(new_level_reachability[level], level_reachability[level]);
            if (level_reachability[level].is_reachable) {
                new_level_reachability[level + new_box.size] = std::max(
                    new_level_reachability[level + new_box.size],
                    {true, (new_box.is_important ? 1 : 0) + level_reachability[level].how_much_important_waisted}
                );
            }
        }
        auto& min_reacability_levels = boxes_count_min_reachability_levels[i + 1];
        for (int level = l; level <= 10000; ++level) {
            if (min_reacability_levels.min_reachable_level_after_l == -1 && new_level_reachability[level].is_reachable) {
                min_reacability_levels.min_reachable_level_after_l = level;
            }
            if (min_reacability_levels.min_reachable_level_after_l_without_one_important == -1
                && new_level_reachability[level].is_reachable && new_level_reachability[level].how_much_important_waisted < important_boxes) {
                min_reacability_levels.min_reachable_level_after_l_without_one_important = level;
            }
        }
        level_reachability = std::move(new_level_reachability);
    }
    int comfortability = 0;
    int used_boxes = n;
    while (true) {
        if (used_boxes == 0 || !a[used_boxes - 1].is_important) {
            break;
        } else if (
            boxes_count_min_reachability_levels[used_boxes - 1].min_reachable_level_after_l >= 0
            && boxes_count_min_reachability_levels[used_boxes - 1].min_reachable_level_after_l + a[used_boxes - 1].size <= r
        ) {
            r -= a[used_boxes - 1].size;
            ++comfortability;
            --used_boxes;
        } else if (
            boxes_count_min_reachability_levels[used_boxes].min_reachable_level_after_l_without_one_important >= 0
            && boxes_count_min_reachability_levels[used_boxes].min_reachable_level_after_l_without_one_important <= r
        ) {
            ++comfortability;
            break;
        } else {
            break;
        }
    }
    std::cout << comfortability << std::endl;
    return 0;
}
