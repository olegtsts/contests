#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>

std::tuple<int, int> GetResponse(const int x, const int y) {
    std::cout << x << " " << y << std::endl << std::flush;
//    std::cerr << "Offering " << x << " " << y << std::endl;
    int response_x, response_y;
    std::cin >> response_x >> response_y;
//    std::cerr << "Getting " << response_x << " " << response_y << std::endl;
    if (response_x == -1) {
        throw std::logic_error("bad response: -1");
    }
    return std::make_tuple(response_x, response_y);
}

void DoTest() {
    int a;
    std::cin >> a;
//    std::cerr << "Starting test" << std::endl;
    int edge = static_cast<int>(ceil(sqrt(static_cast<double>(a))));
    edge = (edge + 2) / 3 * 3;
    std::vector<std::vector<bool>> filled_cells(edge, std::vector<bool>(edge, false));
    int cur_x = 2;
    int cur_y = 2;
    int cur_filled_in_small_rectangle = 0;
    int responses_count = 0;
    while (true) {
        int res_x, res_y;
        std::tie(res_x, res_y) = GetResponse(cur_x, cur_y);
        ++responses_count;
        if (res_x == 0 && res_y == 0) {
//            std::cerr << "Done in " << responses_count << " resposes\n";
            return;
        }
        if (!filled_cells[res_x - 1][res_y - 1]) {
            filled_cells[res_x - 1][res_y - 1] = true;
            ++cur_filled_in_small_rectangle;
        }
        if (cur_filled_in_small_rectangle == 9) {
            cur_x += 3;
            if (cur_x > edge - 1) {
                cur_x = 2;
                cur_y += 3;
            }
            cur_filled_in_small_rectangle = 0;
        }
    }
}
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        DoTest();
    }
    return 0;
}
