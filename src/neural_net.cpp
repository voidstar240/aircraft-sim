#include "neural_net.h"
#include "math_funcs.h"
#include <iostream>
#include <vector>


std::vector<double> train_classifier(const std::vector<Aircraft>& training_data,
                                     const std::vector<double> w_0,
                                     const double a,
                                     const uint32_t iterations) {
    // pre allocate to avoid reallocations
    std::vector<double> x(3, 0.00);
    std::vector<double> w = w_0;

    for (uint32_t n = 0; n < iterations; n++) {
        for (auto aircraft : training_data) {
            // set values in x vector
            x[0] = aircraft.approach_speed;
            x[1] = aircraft.wingspan;
            x[2] = aircraft.mtow;

            // set the expected output
            double y = (double)aircraft.has_jet_engine;
            const std::vector<double> w_new =
                update_weights(w, gradient_weights(w, x, y), a);
            // set the old weights to the new weights
            w[0] = w_new[0];
            w[1] = w_new[1];
            w[2] = w_new[2];
        }
    }
    return w;
}
