#pragma once
#include <vector>

double dot_product(const std::vector<double>& u, const std::vector<double>& v);
double sigmoid(const double z);
double gradient_sigmoid(const double z);
double gradient_cost(const double y_pred, const double y);
std::vector<double> gradient_weights(const std::vector<double>& w,
                                     const std::vector<double>& x,
                                     const double y);
std::vector<double> update_weights(const std::vector<double>& w,
                                   const std::vector<double>& dw,
                                   const double a);
