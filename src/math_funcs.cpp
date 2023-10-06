#include "math_funcs.h"
#include <cstdint>
#include <stdexcept>
#include <cmath>

double dot_product(const std::vector<double> u, const std::vector<double> v) {
    if (u.size() != v.size()) {
        throw std::invalid_argument("Vectors passed into function `dot_product` have different size");
    }

    double sum = 0;
    for (size_t i = 0; i < u.size(); i++) {
        sum += u[i] * v[i];
    }
    return sum;
}

double sigmoid(const double z) {
    return 1.0 / (1.0 + std::exp(-1.0 * z));
}

double gradient_sigmoid(const double z) {
    return sigmoid(z) * (1.0 - sigmoid(z));
}

double gradient_cost(const double y_pred, const double y) {
    return 2 * (y_pred - y);
}
