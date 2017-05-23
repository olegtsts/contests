#include <iostream>
#include <algorithm>
#include <vector>

int main () {
    long long int n,f;
    std::cin >> n >> f;

    long long int current_score = 0;
    std::vector<long long int> score_modifications(n);
    for (size_t i = 0; i < n; ++i) {
        long long int k, l;
        std::cin >> k >> l;
        current_score += std::min(k, l);
        score_modifications[i] = - std::min(2 * k, l) + std::min(k, l);
    }
    std::sort(score_modifications.begin(), score_modifications.end());
    for (size_t i = 0; i < f; ++i) {
        current_score -= score_modifications[i];
    }
    std::cout << current_score << std::endl;
    return 0;
}
