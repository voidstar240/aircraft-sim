#include "math_funcs.h"
#include <cstdint>
#include <stdexcept>


double dot_product(std::vector<double> u, std::vector<double> v) {
    if (u.size() != v.size()) {
        throw std::invalid_argument("Vectors passed into function `dot_product` have different size");
    }

    double sum = 0;
    for (size_t i = 0; i < u.size(); i++) {
        sum += u[i] * v[i];
    }
    return sum;
}
