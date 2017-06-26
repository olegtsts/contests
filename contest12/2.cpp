#include <iostream>
#include <cmath>

void update_max(long long int m, long long int b, long long int y, long long int& result_max) {
    if (y >= 0 && y <= b) {
        long long int x = m * (b - y);
        long long int res = (x + 1) * (y + 1) * (x + y) / 2;
        if (result_max < res) {
            result_max = res;
        }
    }
}

int main() {
    long long int m,b;
    std::cin >> m >> b;
    long long int result_max = 0;
    for (int i = 0; i < b; ++i) {
        update_max(m,b,i,result_max);
    }
//    double a = 3 * (m * m - m);
//    double b2 = 2 * (- 2*b*m*m + b*m + m*m - 2*m + 1);
//    double c = (b*b*m*m - 2 * b * m * m + 2 * b * m - m + 1);
//
//    long long int result_max = 0;
//    if (a != 0) {
//        double first_root = double(-b2 + sqrt(double(b2 * b2 - 4 * a * c))) / 2;
//        double second_root = double(-b2 - sqrt(double(b2 * b2 - 4 * a * c))) / 2;
//        update_max(m,b,first_root,result_max);
//        update_max(m,b,second_root,result_max);
//    } else if (b != 0) {
//        update_max(m,b,-c/b2, result_max);
//    } else {
//        update_max(m,b,0,result_max);
//    }
//    update_max(m,b,0,result_max);
//    update_max(m,b,b,result_max);
    std::cout << result_max << std::endl;
    return 0;
}
