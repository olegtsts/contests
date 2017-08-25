#include <cstdlib>
#include <fstream>
#include <iostream>

int main() {
    for (int i = 0; i < 100; ++i) {
        std::ofstream fh("file");
        int n = 750;
        fh << n << std::endl;
        for (int i = 0; i < n; ++i) {
            long long int x1, x2, y1, a, b, y2;
            x1 = rand() % 20;
            x2 = rand() % 20;
            y1 = rand() % 10;
            y2 = rand() % 10;
            a = rand() % 10;
            b = rand() % 10;
            fh << x1 << " " << x2 << " " << y1 << " " << a << " " << b << " " << y2 << std::endl;
        }
        long long int m = 500;
        fh << m << std::endl;
        for (int i = 0; i < m; ++i) {
            long long int l, r, x;
            l = rand() % n;
            r = rand() % n;
            x = rand() % 10;
            fh << l + 1 << " " << r + 1 << " " << x << std::endl;
        }
        fh.close();
        if (system("./7-timelimit.out < file > 7-timelimit.res")) {
            throw std::logic_error("pre program failed");
        }
        if (system("./a-with-tree.out < file > a-with-tree.res")) {
            throw std::logic_error("tested program failed");
        }
        if (system("diff 7-timelimit.res a-with-tree.res")) {
            throw std::logic_error("results differ");
        } else {
            std::cout << "OK\n";
        }
    }
    return 0;
}

