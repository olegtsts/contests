#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip>

int main() {
    int n, t_s, t_f;
    long double c_n, c_s, c_f;
    std::cin >> n >> c_n >> c_f >> c_s >> t_f >> t_s;
    int f_pool = 0;
    int s_pool = 0;
    long double c_min = std::min(std::min(c_n, c_s), c_f);
    long double result_cost = 0;
    std::vector<int> rs(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> rs[i];
        int r = rs[i];
        if (i >= t_f) {
            f_pool += rs[i - t_f];
        }
        if (i >= t_s) {
            s_pool += rs[i - t_s];
        }
//        std::cout  << " r = " << r << " i = " << i << " s_pool = " << s_pool << " f_pool = " << f_pool << " result_cost = " << result_cost << std::endl;
        while (r > 0) {
            if (c_min == c_n) {
                result_cost += c_n * r;
                r = 0;
            } else if (s_pool > 0) {
                int s_pool_use = std::min(r, s_pool);
                result_cost += c_s * s_pool_use;
                s_pool -= s_pool_use;
                r -= s_pool_use;
            } else if (f_pool > 0) {
                int f_pool_use = std::min(r, f_pool);
                result_cost += c_f * f_pool_use;
                f_pool -= f_pool_use;
                r -= f_pool_use;
            } else {
                result_cost += c_n * r;
                r = 0;
            }
        }
//        std::cout  << "i = " << i << " s_pool = " << s_pool << " f_pool = " << f_pool << " result_cost = " << result_cost << std::endl;
    }

    std::cout << std::setprecision(10) << result_cost << std::endl;

    return 0;
}
