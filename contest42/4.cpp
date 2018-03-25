#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

struct Ratio {
    long long int numerator;
    long long int denominator;
    long long int index;

    bool operator<(const Ratio& other) const {
        long long int first_numerator = numerator;
        long long int first_denominator = denominator;
        if (denominator < 0) {
            first_denominator = -first_denominator;
            first_numerator = - first_numerator;
        }
        long long int second_numerator = other.numerator;
        long long int second_denominator = other.denominator;
        if (other.denominator < 0) {
            second_denominator = -second_denominator;
            second_numerator = -second_numerator;
        }
        return std::forward_as_tuple(first_numerator * second_denominator, other.index)
            < std::forward_as_tuple(second_numerator * first_denominator, index);
    }

    long double GetDoubleRepresentation() const {
        return static_cast<long double>(numerator) / denominator;
    }

    friend std::ostream& operator<<(std::ostream& out, const Ratio& ratio) {
        return out << ratio.GetDoubleRepresentation();
    }
};

template<typename T>
long long int GetInversionsCountRecursive(std::vector<T>& data, std::vector<T>& another_data, const size_t start_index,const size_t finish_index) {
    if (start_index == finish_index) {
        return 0;
    } else if (start_index + 1 == finish_index) {
        return 0;
    } else {
        size_t middle_index = (finish_index + start_index) / 2;
        long long int inversions = 0;
        inversions += GetInversionsCountRecursive(data, another_data, start_index, middle_index);
        inversions += GetInversionsCountRecursive(data, another_data, middle_index, finish_index);
        size_t first_index = start_index;
        size_t second_index = middle_index;
        size_t target_index = start_index;
        while (first_index < middle_index && second_index < finish_index) {
            if (data[first_index] < data[second_index]) {
                another_data[target_index++] = data[first_index++];
            } else {
                inversions += middle_index - first_index;
                another_data[target_index++] = data[second_index++];
            }
        }
        while (first_index < middle_index) {
            another_data[target_index++] = data[first_index++];
        }
        while (second_index < finish_index) {
            another_data[target_index++] = data[second_index++];
        }
        for (size_t i = start_index; i < finish_index; ++i) {
            data[i] = another_data[i];
        }
        return inversions;
    }
}

template<typename T>
long long int GetInversionsCount(std::vector<T>& data) {
    std::vector<T> another_data(data.size());
    return GetInversionsCountRecursive(data, another_data, 0, data.size());
}

int main() {
    long long int n;
    long long int w;
    std::cin >> n >> w;
    std::vector<long long int> v(n);
    std::vector<long long int> x(n);
    std::vector<long long int> points(n);
    for (long long int i = 0; i < n; ++i) {
        std::cin >> x[i] >> v[i];
        points[i] = i;
    }
    std::sort(points.begin(), points.end(), [&](const long long int first, const long long int second) {
        return std::forward_as_tuple(Ratio{x[first], v[first] - w, 0}, Ratio{-x[first], v[first] + w, 0})
            < std::forward_as_tuple(Ratio{x[second], v[second] - w, 0}, Ratio{-x[second], v[second] + w, 0});
    });
    std::vector<Ratio> ratios(n);
    long long int i = 0;
    for (auto& point_index: points) {
        ratios[i] = {x[point_index], v[point_index] + w, i};
        ++i;
    }
    std::cout << GetInversionsCount(ratios) << std::endl;
    return 0;
}
