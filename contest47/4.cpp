#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

struct Point {
    long double x;
    long double y;
    long double z;
};

std::vector<std::vector<long double>> GetMatrixSum(
    const std::vector<std::vector<long double>>& first_matrix,
    const std::vector<std::vector<long double>>& second_matrix
) {
    std::vector<std::vector<long double>> third_matrix = first_matrix;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            third_matrix[i][j] += second_matrix[i][j];
        }
    }
    return third_matrix;
}

std::vector<std::vector<long double>> GetProduct(
    const std::vector<std::vector<long double>>& first_matrix,
    const std::vector<std::vector<long double>>& second_matrix
) {
    std::vector<std::vector<long double>> third_matrix(3, std::vector<long double>(3, 0));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                third_matrix[i][k] += first_matrix[i][j] * second_matrix[j][k];
            }
        }
    }
    return third_matrix;
}

long double GetScalarProduct(
    const std::vector<long double>& first_vector,
    const std::vector<long double>& second_vector
) {
    long double product = 0;
    for (int i = 0; i < 3; ++i) {
        product += first_vector[i] * second_vector[i];
    }
    return product;
}

std::vector<long double> GetVectorProduct(
    const std::vector<long double>& first_vector,
    const std::vector<long double>& second_vector
) {
    return {
        first_vector[1] * second_vector[2] - first_vector[2] * second_vector[1],
        first_vector[2] * second_vector[0] - first_vector[0] * second_vector[2],
        first_vector[0] * second_vector[1] - first_vector[1] * second_vector[0]
    };
}

long double GetVectorLength(
    const std::vector<long double>& input_vector
) {
    return sqrt(GetScalarProduct(input_vector, input_vector));
}

std::vector<std::vector<long double>> GetIdentityMatrix() {
    std::vector<std::vector<long double>> matrix(3, std::vector<long double>(3, 0));
    for (int i = 0; i < 3; ++i) {
        matrix[i][i] = 1;
    }
    return matrix;
}

std::vector<std::vector<long double>> GetProductOfMatrixAndScalar(
    const std::vector<std::vector<long double>> input_matrix,
    const long double scalar
) {
    std::vector<std::vector<long double>> result_matrix = input_matrix;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result_matrix[i][j] *= scalar;
        }
    }
    return result_matrix;
}

std::vector<std::vector<long double>> GetRotationMatrix(
    const std::vector<long double>& first_vector,
    const std::vector<long double>& second_vector
) {
    auto v = GetVectorProduct(first_vector, second_vector);
    auto c = GetScalarProduct(first_vector, second_vector);
    std::vector<std::vector<long double>> v_x = {
        {0, -v[2], v[1]},
        {v[2], 0, -v[0]},
        {-v[1], v[0], 0}
    };
    return GetMatrixSum(GetMatrixSum(GetIdentityMatrix(), v_x), GetProductOfMatrixAndScalar(GetProduct(v_x, v_x), 1. / (1. + c)));
}

std::vector<long double> GetProductOfMatrixAndVector(
    const std::vector<std::vector<long double>>& input_matrix,
    const std::vector<long double>& input_vector
) {
    std::vector<long double> result_vector(3, 0);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result_vector[i] += input_matrix[i][j] * input_vector[j];
        }
    }
    return result_vector;
}

void OutputVector(const std::vector<long double>& input_vector) {
    for (int i = 0; i < 3; ++i) {
        std::cout << input_vector[i] << " ";
    }
    std::cout << std::endl;
}

void OutputMatrix(const std::vector<std::vector<long double>>& input_matrix) {
    for (int i = 0; i < 3; ++i) {
        OutputVector(input_matrix[i]);
    }
}

std::vector<std::vector<long double>> DoTest() {
    long double x;
    std::cin >> x;
    long double a,b,c;
    if (x * x > 1.999) {
        long double root = sqrt(.5 - x * x / 6);
        a = x / 3 + root;
        b = x / 3;
        c = x / 3 - root;
    } else {
        long double root = sqrt(.5 - .25 * x * x);
        a = x / 2 - root;
        b = x / 2 + root;
        c = 0;
    }
    auto rotation_matrix = GetRotationMatrix({a, b, c}, {0, 1, 0});
    return {
        GetProductOfMatrixAndVector(rotation_matrix, std::vector<long double>{.5, 0, 0}),
        GetProductOfMatrixAndVector(rotation_matrix, std::vector<long double>{0, .5, 0}),
        GetProductOfMatrixAndVector(rotation_matrix, std::vector<long double>{0, 0, .5})
    };
}

int main() {
    std::cout << std::setprecision(20);
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cout << "Case #" << i + 1 << ":\n";
        std::vector<std::vector<long double>> points = DoTest();
        for (auto& point: points) {
            std::cout << point[0] << " " << point[1] << " " << point[2] << std::endl;
        }
    }
    return 0;
}
