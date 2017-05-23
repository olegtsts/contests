#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main() {
    int offices;
    std::cin >> offices;
    std::vector<std::string> hour_office_place(24 * offices, "");
    std::unordered_map<std::string, int> office_index;
    for (size_t i = 0; i < offices; ++i) {
        std::string office;
        int rooms;
        std::cin >> office >> rooms;
        office_index[office] = i;
        for (size_t j = 0; j < rooms; ++j) {
            std::string busy_string, room;
            std::cin >> busy_string >> room;
            for (size_t k = 0; k < 24; ++k) {
                char busy_symbol = busy_string[k];
                if (busy_symbol == '.') {
                    hour_office_place[24 * i + k] = room;
                }
            }
        }
    }
    int m;
    std::cin >> m;
    for (size_t i = 0; i < m; ++i) {
        int l;
        std::cin >> l;
        std::vector<int> offices(l);
        for (size_t j = 0; j < l; ++j) {
            std::string office;
            std::cin >> office;
            offices[j] = office_index[office];
        }
        std::vector<std::string> rooms(l);

        bool offices_found = false;
        for (size_t k = 0; k < 24; ++k) {
            offices_found = true;
            for (size_t j = 0; j < l; ++j) {
                std::string& place = hour_office_place[24 * offices[j] + k];
                if (place != std::string("")) {
                    rooms[j] = place;
                } else {
                    offices_found = false;
                    break;
                }
            }
            if (offices_found) {
                break;
            }
        }
        if (offices_found) {
            std::cout << "Yes";
            for (size_t j = 0; j < l; ++j) {
                std::cout << " " << rooms[j];
            }
        } else {
            std::cout << "No";
        }
        std::cout << std::endl;
    }
    return 0;
}

