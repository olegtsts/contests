#include <iostream>
#include <cstdlib>

int main() {
    int skip;
    int n;
    int bonus;
    std::cin >> skip >> skip >> skip >> n >> bonus >> skip;
    int first_total_bonus = 0;
    int second_total_bonus = 0;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2, s, f;
        std::cin >> x1 >> y1 >> x2 >> y2 >> s >> f;
        first_total_bonus += abs(x1 - x2) + abs(y1 - y2);
        second_total_bonus += abs(x1 - x2) + abs(y1 - y2) + bonus;
    }
    std::cout << first_total_bonus << " " << second_total_bonus << std::endl;
    return 0;
}
