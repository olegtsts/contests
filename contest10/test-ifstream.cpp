#include <fstream>
#include <iostream>

int main () {
    std::ifstream ifh("out.txt");
    while (!ifh.eof()) {
        int a,b,c;
        ifh >> a >> b >> c;
        if (!ifh.eof()) {
            std::cout << a << b << c << std::endl;
        }
    }
    return 0;
}
