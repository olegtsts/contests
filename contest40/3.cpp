#include <iostream>
#include <set>
#include <vector>

struct SnowDrift {
    long long int size;
    long long int index;
    bool operator<(const SnowDrift& other) const {
        return std::forward_as_tuple(size, index) < std::forward_as_tuple(other.size, other.index);
    }
};

int main() {
    long long int n;
    std::cin >> n;
    std::vector<long long int> sizes(n);
    std::vector<long long int> temps(n);
    std::set<SnowDrift> drifts;
    long long int days_passed = 0;
    for (long long int i = 0; i < n; ++i) {
        std::cin >> sizes[i];
    }
    for (long long int i = 0;i < n; ++i) {
        std::cin >> temps[i];
    }
    std::vector<long long int> prefix_temps_sums(n + 1, 0);
    prefix_temps_sums[0] = 0;
    for (long long int i = 0; i < n; ++i) {
        prefix_temps_sums[i + 1] = prefix_temps_sums[i] + temps[i];
    }

    for (long long int i = 0; i < n; ++i) {
        long long int melted_today = 0;
        drifts.insert(SnowDrift{sizes[i] + prefix_temps_sums[i], i});
        ++days_passed;
        std::vector<SnowDrift> drifts_to_remove;
        melted_today += drifts.size() * temps[i];
        for (auto drift: drifts) {
            if (drift.size < prefix_temps_sums[i + 1]) {
                melted_today += drift.size - prefix_temps_sums[i + 1];
                drifts_to_remove.push_back(drift);
            } else {
                break;
            }
        }
        for (auto drift: drifts_to_remove) {
            drifts.erase(drift);
        }
        std::cout << melted_today << " ";
    }
    std::cout << std::endl;
    return 0;
}
