#include <numeric>
#include <iostream>
#include <vector>
#include <cmath>

const long long int MODULO = 1000000007;

long long int GetPowerOfTwo(int input_power) {
    long long int x = 1ll;
    long long int base = 2ll;
    while (input_power > 0) {
        if (input_power % 2 == 0) {
            base *= base;
            base %= MODULO;
            input_power /= 2;
        } else {
            --input_power;
            x *= base;
            x %= MODULO;
        }
    }
    return x;
}

long long int gcd (long long int a, long long int b, long long int & x, long long int & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	long long int x1, y1;
	long long int d = gcd (b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

class Fraction {
public:
    Fraction(const long long int numerator, const long long int denominator)
        : numerator(numerator)
        , denominator(denominator)
    {}

    Fraction operator+(const Fraction& other) const {
        Fraction res{0, 0};
        res.numerator += numerator * other.denominator;
        res.numerator %= MODULO;
        res.numerator += other.numerator * denominator;
        res.numerator %= MODULO;
        res.denominator += denominator * other.denominator;
        res.denominator %= MODULO;
        return res;
    }

    Fraction& operator+=(const Fraction& other) {
        *this = *this + other;
        return *this;
    }

    long double GetDoubleRepresentation() const {
        return static_cast<long double>(numerator) / denominator;
    }

    void Output() const {
        std::cout << numerator << "/" << denominator << std::endl;
    }

    long long int GetNumericRepresentation() const {
        long long int x,y;
        gcd(denominator, MODULO, x, y);
        long long int result = numerator;
        result *= x;
        result %= MODULO;
        result += MODULO;
        result %= MODULO;
        return result;
    }
private:
    long long int numerator;
    long long int denominator;
};

struct BlackNeighbour {
    int identificator = 0;
    long long int prev_counter_value = 0;

    BlackNeighbour(const int identificator, const long long int prev_counter_value)
        : identificator(identificator)
        , prev_counter_value(prev_counter_value)
    {}
};

int main() {
    std::ios::sync_with_stdio(false);
    int n,m,k;
    std::cin >> n >> m >> k;
    std::vector<long long int> weights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
    std::vector<int> sequence(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> sequence[i];
        --sequence[i];
    }
    std::vector<std::vector<int>> neighbours(n);
    for (int i = 0; i < m; ++i) {
        int first_node, second_node;
        std::cin >> first_node >> second_node;
        --first_node;
        --second_node;
        neighbours[first_node].push_back(second_node);
        neighbours[second_node].push_back(first_node);
    }
    std::vector<int> counts_of_decrease(n, 0);
    for (int i = 0; i < k; ++i) {
        ++counts_of_decrease[sequence[i]];
    }
    std::vector<long long int> denominators(n, 1ll);
    Fraction res{0ll, 1ll};
    std::vector<bool> is_black(n, false);
    size_t black_vertex_boundary = ceil(sqrt(static_cast<double>(n)));
    for (int i = 0; i < n; ++i) {
        is_black[i] = neighbours[i].size() > black_vertex_boundary;
    }
    std::vector<std::vector<BlackNeighbour>> black_neighbours(n);
    for (int i = 0; i < n; ++i) {
        for (auto neighbour: neighbours[i]) {
            if (is_black[neighbour]) {
                black_neighbours[i].push_back(BlackNeighbour{neighbour, 0});
            }
        }
    }
    std::vector<long long int> black_accumulative_counters(n, 0);
    for (int i = 0; i < k; ++i) {
        int current = sequence[i];
        for (auto& neighbour: black_neighbours[current]) {
            if (counts_of_decrease[current] == 0 && weights[current] > 0) {
                std::cout << "-1\n";
                return 0;
            }
            if (weights[current] > 0) {
                long long int power_of_two = GetPowerOfTwo(counts_of_decrease[current]);
                long long int numerator = power_of_two;
                long long int denominator = power_of_two - 1ll;
                denominator *= denominators[current];
                denominator %= MODULO;
                numerator *= weights[current];
                numerator %= MODULO;
                numerator *= (black_accumulative_counters[neighbour.identificator] - neighbour.prev_counter_value);
                numerator %= MODULO;
                neighbour.prev_counter_value = black_accumulative_counters[neighbour.identificator];
                res += Fraction{numerator, denominator};
            }
        }
        if (is_black[current]) {
            ++black_accumulative_counters[current];
        } else {
            for (auto& neighbour: neighbours[current]) {
                if (counts_of_decrease[neighbour] == 0 && weights[neighbour] > 0) {
                    std::cout << "-1\n";
                    return 0;
                }
                if (weights[neighbour] > 0) {
                    long long int power_of_two = GetPowerOfTwo(counts_of_decrease[neighbour]);
                    long long int numerator = power_of_two;
                    long long int denominator = power_of_two - 1ll;
                    denominator *= denominators[neighbour];
                    denominator %= MODULO;
                    numerator *= weights[neighbour];
                    numerator %= MODULO;
                    res += Fraction{numerator, denominator};
                }
            }
        }
        denominators[current] *= 2ll;
        denominators[current] %= MODULO;
    }
    for (int i = 0; i < n; ++i) {
        for (auto& neighbour: black_neighbours[i]) {
            if (counts_of_decrease[i] == 0 && weights[i] > 0) {
                std::cout << "-1\n";
                return 0;
            }
            if (weights[i] > 0) {
                long long int power_of_two = GetPowerOfTwo(counts_of_decrease[i]);
                long long int numerator = power_of_two;
                long long int denominator = power_of_two - 1ll;
                denominator *= denominators[i];
                denominator %= MODULO;
                numerator *= weights[i];
                numerator %= MODULO;
                numerator *= (black_accumulative_counters[neighbour.identificator] - neighbour.prev_counter_value);
                numerator %= MODULO;
                neighbour.prev_counter_value = black_accumulative_counters[neighbour.identificator];
                res += Fraction{numerator, denominator};
            }
        }
    }
    std::cout << res.GetNumericRepresentation() << std::endl;
}
