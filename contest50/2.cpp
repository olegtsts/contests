#include <iostream>
#include <vector>
#include <algorithm>

enum class Seat {EMPTY, PROF, PROG, SPORT};

int main() {
    int n;
    int prog,sport;
    std::cin >> n >> prog >> sport;
    std::vector<Seat> who_is_sitting(n, Seat::EMPTY);
    Seat prev_seat = Seat::PROF;
    int total_count = 0;
    for (int i = 0; i < n; ++i) {
        Seat cur_seat;
        char symbol;
        std::cin >> symbol;
        if (symbol == '*') {
            cur_seat = Seat::PROF;
        } else {
            if (prev_seat == Seat::SPORT && prog > 0) {
                --prog;
                ++total_count;
                cur_seat = Seat::PROG;
            } else if (prev_seat == Seat::PROG && sport > 0) {
                --sport;
                ++total_count;
                cur_seat = Seat::SPORT;
            } else if ((prev_seat == Seat::PROF || prev_seat == Seat::EMPTY) && std::max(prog, sport) > 0) {
                if (prog > sport) {
                    --prog;
                    ++total_count;
                    cur_seat = Seat::PROG;
                } else {
                    --sport;
                    ++total_count;
                    cur_seat = Seat::SPORT;
                }
            } else {
                cur_seat = Seat::EMPTY;
            }
        }
        prev_seat = cur_seat;
    }
    std::cout << total_count << std::endl;
    return 0;
}
