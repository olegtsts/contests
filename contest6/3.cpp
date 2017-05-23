#include <iostream>
#include <vector>

int main() {
    long long int n;
    double p;
    std::cin >> n >> p;
    std::vector<double> charges(n);
    std::vector<double> speeds(n);
    double speeds_sum = 0;
    double charges_sum = 0;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> speeds[i] >> charges[i];
        speeds_sum += speeds[i];
        charges_sum += charges[i];
    }
    if (p >= speeds_sum) {
        std::cout << -1 << std::endl;
    } else {
        double good_t = 0;
        double bad_t = charges_sum / (speeds_sum - p);
        while (bad_t - good_t > 1e-5) {
            double middle_t = (bad_t + good_t) / 2;
            double needs = 0;
            for (size_t i = 0; i < n; ++i) {
                if (middle_t * speeds[i] >= charges[i]) {
                    needs += middle_t * speeds[i] - charges[i];
                }
            }
            if (needs > middle_t * p) {
                bad_t = middle_t;
            } else {
                good_t = middle_t;
            }
        }
        std::cout << good_t << std::endl;
    }
    return 0;
}
