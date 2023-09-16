#include "integrator.h"

IntegrationData euler_integrate(const RateFunction rate_func,
                                const std::vector<double> initial_vals,
                                const double t_init,
                                const double dt,
                                const size_t steps) {
    // Init structure for output data
    IntegrationData data = IntegrationData(steps, initial_vals.size());
    // set initial conditions
    data.set_time(0, t_init);
    for (size_t i = 0; i < initial_vals.size(); i++) {
        data.get_state(0)[i] = initial_vals[i];
    }

    // iterate for all steps
    for (size_t i = 0; i < steps - 1; i++) {
        data.set_time(i + 1, t_init + (dt * (i + 1)));
        data.get_state(i + 1);
        std::vector<double> rates = rate_func(data.get_time(i), data.get_state(i));
        // integrate all state variables
        for (size_t j = 0; j < rates.size(); j++) {
            // x_t+1 = x_t + x_dot * dt
            data.get_state(i + 1)[j] = data.get_state(i)[j] + rates[j] * dt;
        }
    }

    return data;
}
