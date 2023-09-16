#include <cstdint>
#include <vector>

// params: time, cur state
// return: next state
typedef std::vector<double> (*RateFunction)(double, double*);

class IntegrationData {
private:
    double* data;
    size_t steps;
    size_t state_vars;

public:
    IntegrationData(size_t num_steps, size_t num_state_vars) {
        this->data = new double[num_steps * (num_state_vars + 1)];
        this->steps = num_steps;
        this->state_vars = num_state_vars + 1;
    }

    ~IntegrationData() {
        delete [] this->data;
    }

    inline size_t get_steps() { return this->steps; }
    inline size_t get_state_vars() { return this->state_vars; }

    inline double get_time(size_t step) { return this->data[step * this->state_vars]; }
    inline double* get_state(size_t step) { return this->data + (step * this->state_vars) + 1; }

    inline void set_time(size_t step, double time) { this->data[step * this->state_vars] = time; }
};

// Numerically integrates `rate_func` using the forward Euler method
IntegrationData euler_integrate(RateFunction rate_func, std::vector<double> initial_vals,
                        double t_init, double dt, size_t steps);
