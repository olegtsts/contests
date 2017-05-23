#include <iostream>
#include <vector>

int main() {
    long long int n;
    std::cin >> n;

    long long int sum = 0;
    std::vector<long long int> forces;
    for (size_t i = 0; i < n; ++i) {
        long long int force;
        std::cin >> force;
        sum += force;
        forces.push_back(force);
    }
    long long int needed_force = sum / 2;
    bool deleted_one = false;
    for (auto& force: forces) {
        if (force == needed_force && deleted_one == false) {
            deleted_one = true;
        } else {
            std::cout << force << " ";
        }
    }
    std::cout << needed_force << std::endl;
    return 0;
}

