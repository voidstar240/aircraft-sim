#pragma once
#include <cstdint>
#include <vector>

// params: time, cur state
// return: next state
typedef std::vector<double> (*RateFunction)(const double, const double*);

// A flat matrix to contain the state at all integrated time steps.
// State at the time steps are stored as a 1D array where every `num_state_vars`
// elements is a new row. This is done to decrease the number of pointer
// indirections needed to access the data. This has the result of improving
// cache locality.
class IntegrationData {
private:
    double* data; // where the raw state data is stored. DO NOT READ DIRECTLY
    size_t steps; // the number of steps in the integration
    size_t state_vars; // the number of state variables that describe the system

public:
    IntegrationData(const size_t num_steps, const size_t num_state_vars) {
        // allocate enough memory to hold the initial condition
        // and all states over time
        this->data = new double[num_steps * (num_state_vars + 1)];
        this->steps = num_steps;
        this->state_vars = num_state_vars + 1;
    }

    ~IntegrationData() {
        delete [] this->data; // free the allocated data
    }

    // Basic getters (inlined to avoid function indirections)
    inline size_t get_steps() const { return this->steps; }
    inline size_t get_state_vars() const { return this->state_vars; }

    inline double get_time(const size_t step) const
    { return this->data[step * this->state_vars]; }

    inline double* get_state(const size_t step) const
    { return this->data + (step * this->state_vars) + 1; }


    inline void set_time(const size_t step, const double time)
    { this->data[step * this->state_vars] = time; }
};

// Numerically integrates `rate_func` using the forward Euler method
IntegrationData euler_integrate(const RateFunction rate_func,
                                const std::vector<double>& initial_vals,
                                const double t_init,
                                const double dt,
                                const size_t steps);
