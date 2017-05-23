#include <iostream>
#include <algorithm>

int main () {
    std::vector<long long int> edges(4);
    std::cin >> edges[0] >> edges[1] >> edges[2] >> edges[3];
    std::sort(edges.begin(), edges.end());
    if (edges[0] + edges[3] == edges[1] + edges[2]) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
    return 0;
}
