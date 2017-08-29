#include <iostream>

int main() {
    int s, v1, v2, t1, t2;
    std::cin >> s >> v1 >> v2 >> t1 >> t2;
    int first_time = s * v1 + 2 * t1;
    int second_time = s * v2 + 2 * t2;
    if (first_time < second_time) {
        std::cout << "First\n";
    } else if (first_time > second_time) {
        std::cout << "Second\n";
    } else {
        std::cout << "Friendship\n";
    }
    return 0;
}
