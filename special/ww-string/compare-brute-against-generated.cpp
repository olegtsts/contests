#include <cstdlib>
#include <fstream>
#include <iostream>

int main() {
    for (int i = 0; i < 100; ++i) {
        std::ofstream fh("input");
        int k = rand() % 5 + 1;
        int n = rand() % 7 + 1;
        int a = rand() % 5 + 1;
        fh << k << " " << n << " " << a << std::endl;
        fh.close();
        if (system("./brute.out < input > 1.output")) {
            throw std::logic_error("test programm failed");
        }
        if (system("./generated.out < input > 2.output 2>/dev/null")) {
            throw std::logic_error("tested programm failed");
        }
        if (system("diff 1.output 2.output")) {
            throw std::logic_error("results differ");
        } else {
            std::cout << "OK\n";
        }
    }
    return 0;
}
