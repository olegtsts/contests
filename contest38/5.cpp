#include <iostream>
#include <cassert>

struct State {
    long long int books_remained;
    long long int day;
    int weekday;
    long long int library_addon;

    long long int GetRemainedAfterDay() const {
        long long int new_books_remained = books_remained;
        if (weekday != 5 && weekday != 6) {
            new_books_remained += library_addon;
        }
        new_books_remained -= day;
        return new_books_remained;
    }
    bool IsDayOk() const {
        return GetRemainedAfterDay() >= 0;
    }
    void MoveDay() {
        books_remained = GetRemainedAfterDay();
        ++day;
        ++weekday;
        weekday %= 7;
    }
    bool CheckWeeksCount(const long long int weeks_count) const {
        return (
            books_remained + 5ll * weeks_count * library_addon >= 7ll * weeks_count * day + (7ll * weeks_count - 1ll) * 7ll * weeks_count / 2
        );
    }
    long long int GetWeeksCount() const {
        long long int lower_weeks_count = 0ll;
        long long int upper_weeks_count = 400000000ll;
        while (lower_weeks_count + 1 < upper_weeks_count) {
            long long int middle_weeks_count = (lower_weeks_count + upper_weeks_count) / 2;
            if (CheckWeeksCount(middle_weeks_count)) {
                lower_weeks_count = middle_weeks_count;
            } else {
                upper_weeks_count = middle_weeks_count;
            }
        }
        return lower_weeks_count;
    }
    void MoveWeeks(const long long int weeks_count) {
        books_remained += 5ll * weeks_count * library_addon - (7ll * weeks_count * day + (7ll * weeks_count - 1ll) * 7ll * weeks_count / 2);
        day += 7ll * weeks_count;
    }
};

int main() {
    State state;
    std::cin >> state.library_addon >> state.books_remained >> state.weekday;
    --state.weekday;
    state.day = 1;
    while (state.weekday != 0 && state.IsDayOk()) {
        state.MoveDay();
    }
    if (state.IsDayOk()) {
        long long int weeks_count = state.GetWeeksCount();
        state.MoveWeeks(weeks_count);
        int count_of_times = 0;
        while (state.IsDayOk()) {
            state.MoveDay();
            if (++count_of_times > 10) {
                assert(false);
            }
        }
    }
    std::cout << state.day - 1 << std::endl;
    return 0;
}
