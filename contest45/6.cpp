#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

long long int MODULO = 1000000007;

class BitMatrix {
public:
    BitMatrix()
        : main_numbers()
        , zero_options(1)
    {}

    void ReduceNumber(long long int& number) const {
        while (number > 0) {
            if (main_numbers.size() == 0) {
                break;
            }
            auto lower_it = main_numbers.lower_bound(number);

            bool decreased = false;
            if (lower_it != main_numbers.begin()) {
                --lower_it;
                if ((number ^ (*lower_it)) < number) {
                    number = number ^ (*lower_it);
                    decreased = true;
                }
                ++lower_it;
            }
            if (lower_it != main_numbers.end() && (number ^ (*lower_it)) < number) {
                number = number ^ (*lower_it);
                decreased = true;
            }
            if (!decreased) {
                break;
            }
        }
    }

    void AddNumber(long long int number) {
        ReduceNumber(number);
        if (number == 0) {
            zero_options *= 2;
            zero_options %= MODULO;
        } else {
            main_numbers.insert(number);
        }
    }

    long long int GetOptionsCount(long long int number) const {
        ReduceNumber(number);
        if (number == 0) {
            return zero_options;
        } else {
            return 0;
        }
    }

private:
    std::set<long long int> main_numbers;
    long long int zero_options;
};

int main() {
    std::ios::sync_with_stdio(false);
    int n,q;
    std::cin >> n >> q;
    std::vector<long long int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<BitMatrix> prefix_matrices(n + 1);
    for (int i = 0; i < n; ++i) {
        prefix_matrices[i + 1] = prefix_matrices[i];
        prefix_matrices[i + 1].AddNumber(a[i]);
    }
    for (int j = 0; j < q; ++j) {
        int l, x;
        std::cin >> l >> x;
        std::cout << prefix_matrices[l].GetOptionsCount(x) << std::endl;
    }
    return 0;
}
