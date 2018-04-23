#include <iostream>

int main() {
    int k,n,s,p;
    std::cin >> k >> n >> s >> p;
    int how_much_each_needs = (n + s - 1) / s;
    int how_much_all_need = how_much_each_needs * k;
    int x = (how_much_all_need + p - 1) / p;
    std::cout << x << std::endl;
    return 0;
}
