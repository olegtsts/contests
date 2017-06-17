#include <iostream>
#include <vector>
#include <algorithm>

const long long int MODULO = 1000000007;

void multiply(
    std::vector<long long int>& x,
    std::vector<long long int>& a,
    std::vector<long long int>& swap,
    const int size
) {
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            swap[i * size + k] = 0;
            for (int j = 0; j < size; ++j) {
                swap[i * size + k] += (x[i * size + j] * a[j * size + k] % MODULO);
                swap[i * size + k] %= MODULO;
            }
        }
    }
}

std::vector<long long int> get_identical_matrix(
    const int size
) {
    std::vector<long long int> identical_matrix(size * size, 0);
    for (int i = 0; i < size; ++i) {
        identical_matrix[i * size + i] = 1;
    }
    return identical_matrix;
}

void fast_matrix_multiplication(
    std::vector<long long int>& x,
    std::vector<long long int>& a,
    std::vector<long long int>& swap,
    long long int b,
    const int size
) {
    if (b == 0) {
        return;
    }

    if (b % 2 == 0) {
        multiply(a, a, swap, size);
        fast_matrix_multiplication(x, swap, a, b / 2, size);
    } else {
        multiply(x, a, swap, size);
        fast_matrix_multiplication(swap, a, x, b - 1, size);
        std::copy(swap.begin(), swap.begin() + size * size, x.begin());
    }
}

std::vector<long long int> get_transition_matrix(const int size) {
    std::vector<long long int> transition_matrix(size * size, 0);
    for (int i = 0; i < size; ++i) {
        for (int j = std::max(0, i - 1); j < std::min(size, i + 2); ++j) {
            transition_matrix[i * size + j] = 1;
        }
    }
    return transition_matrix;
}

void apply_matrix_to_vector(
    std::vector<long long int>& vector,
    std::vector<long long int>& matrix,
    std::vector<long long int>& result_vector,
    const int size
) {
    for (int i = 0; i < size; ++i) {
        result_vector[i] = 0;
        result_vector[i] = 0;
        for (int j = 0; j < size; ++j) {
            result_vector[i] += (matrix[i * size + j] * vector[j] % MODULO);
            result_vector[i] %= MODULO;
        }
    }
}

void output_matrix(
    std::vector<long long int>& matrix,
    const int size
)  {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << " " << matrix[i * size + j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void output_vector(
    std::vector<long long int>& vector
) {
    for (size_t i = 0; i < vector.size(); ++i) {
        std::cout << " " << vector[i];
    }
    std::cout << std::endl;
}

int main() {
    int n;
    long long int k;
    std::cin >> n >> k;
    std::vector<long long int> counts(16, 0);
    std::vector<long long int> counts_swap(16, 0);
    std::vector<long long int> swap(16 * 16, 0);
    int prev_size = 1;
    counts[0] = 1;
    for (int i = 0; i < n; ++i) {
        long long int a,b;
        int c;
        std::cin >> a >> b >> c;
        int size = c + 1;
        for (int i = prev_size; i < size; ++i) {
            counts[i] = 0;
        }
        auto transition_matrix = get_transition_matrix(size);
        auto res_matrix = get_identical_matrix(size);
        fast_matrix_multiplication(res_matrix, transition_matrix, swap, std::min(b, k) - a, size);
//        output_vector(counts);
        apply_matrix_to_vector(counts, res_matrix, counts_swap, size);
        std::swap(counts, counts_swap);
//        output_matrix(res_matrix, size);
//        output_vector(counts);
        prev_size = size;
    }
    std::cout << counts[0] << std::endl;
    return 0;
}
