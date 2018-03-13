#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n,m,ds,cs,da,ca;
    std::cin >> n >> m >> ds >> cs >> da >> ca;
    std::vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> h[i];
    }
    std::sort(h.begin(), h.end());
    int max_killed = 0;
    for (int count_of_a = 0; count_of_a <= 100; ++count_of_a) {
        int after_a = m - ca * count_of_a;
        if (after_a >= 0) {
            int how_much_s = after_a / cs;
            int killed = 0;
            for (int i = 0; i < n; ++i) {
                int monster_hp = h[i] - count_of_a * da;
                if (monster_hp <= 0) {
                    ++killed;
                } else {
                    int required_s_to_kill = (monster_hp + ds - 1) / ds;
                    if (required_s_to_kill <= how_much_s) {
                        how_much_s -= required_s_to_kill;
                        ++killed;
                    }
                }
            }
            max_killed = std::max(max_killed, killed);
        }
    }
    std::cout << max_killed << std::endl;
    return 0;
}
