#include "math_funcs.h"
#include <cstdint>
#include <stdexcept>
#include <cmath>

double dot_product(const std::vector<double> u, const std::vector<double> v) {
    if (u.size() != v.size()) {
        throw std::invalid_argument(
            "Vectors passed into function `dot_product` have different size"
        );
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

std::vector<double> gradient_weights(const std::vector<double> w,
                                     const std::vector<double> x,
                                     const double y) {
    if (w.size() != x.size()) {
        throw std::invalid_argument(
            "Vectors passed into function `gradient_weights` have different size"
        );
    }
    
    std::vector<double> dw = std::vector<double>();
    dw.reserve(w.size());
    for (size_t i = 0; i < w.size(); i++) {
        const double dot = dot_product(w, x);
        const double term1 = gradient_cost(dot, y);
        const double term2 = sigmoid(dot) * (1 - sigmoid(dot));
        dw.push_back(term1 * term2 * x[i]);
    }
    return dw;
}

std::vector<double> update_weights(const std::vector<double> w,
                                   const std::vector<double> dw,
                                   const double a) {
    if (w.size() != dw.size()) {
        throw std::invalid_argument(
            "Vectors passed into function `update_weights` have different size"
        );
    }

    std::vector<double> w_out = std::vector<double>();
    w_out.reserve(w.size());
    for (size_t i = 0; i < w.size(); i++) {
        w_out.push_back(w[i] - a * dw[i]);
    }
    return w_out;
}
