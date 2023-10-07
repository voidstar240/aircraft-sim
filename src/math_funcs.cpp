#include "math_funcs.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <stdexcept>

double dot_product(const std::vector<double>& u, const std::vector<double>& v) {
    // ensure both vectors are the same length
    if (u.size() != v.size()) {
        throw std::invalid_argument(
            "Vectors passed into function `dot_product` have different size"
        );
    }

    // multiply each element by the corresponding element then add into `sum`
    double sum = 0;
    for (size_t i = 0; i < u.size(); i++) {
        sum += u[i] * v[i];
    }
    return sum;
}

// calculates sigmoid
double sigmoid(const double z) {
    return 1.0 / (1.0 + std::exp(-1.0 * z));
}

// calculates the derivative of sigmoid
double gradient_sigmoid(const double z) {
    return sigmoid(z) * (1.0 - sigmoid(z));
}

// calculates the derivative of cost
double gradient_cost(const double y_pred, const double y) {
    return 2 * (y_pred - y);
}

std::vector<double> gradient_weights(const std::vector<double>& w,
                                     const std::vector<double>& x,
                                     const double y) {
    // throw error if vectors differ in length
    if (w.size() != x.size()) {
        throw std::invalid_argument(
            "Vectors passed into function `gradient_weights` have different size"
        );
    }

    // pre allocate dw to avoid reallocating on every iteration
    std::vector<double> dw(w.size(), 0.0);
    for (size_t i = 0; i < w.size(); i++) {
        const double dot = dot_product(w, x);
        const double term1 = gradient_cost(dot, y);
        const double term2 = sigmoid(dot) * (1 - sigmoid(dot));
        dw[i] = term1 * term2 * x[i];
    }
    return dw;
}

std::vector<double> update_weights(const std::vector<double>& w,
                                   const std::vector<double>& dw,
                                   const double a) {
    // throw error if vectors differ in length
    if (w.size() != dw.size()) {
        throw std::invalid_argument(
            "Vectors passed into function `update_weights` have different size"
        );
    }

    // pre allocate w_out to avoid reallocating on every iteration
    std::vector<double> w_out(w.size(), 0.0);
    for (size_t i = 0; i < w_out.size(); i++) {
        w_out[i] = w[i] - a * dw[i];
    }
    return w_out;
}
