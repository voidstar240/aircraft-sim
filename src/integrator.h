#include <cstdint>
#include <vector>

// params: time, cur state
// return: next state
typedef std::vector<double> (*RateFunction)(const double, const double*);

class IntegrationData {
private:
    double* data;
    size_t steps;
    size_t state_vars;

public:
    IntegrationData(const size_t num_steps, const size_t num_state_vars) {
        this->data = new double[num_steps * (num_state_vars + 1)];
        this->steps = num_steps;
        this->state_vars = num_state_vars + 1;
    }

    ~IntegrationData() {
        delete [] this->data;
    }

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
                                const std::vector<double> initial_vals,
                                const double t_init,
                                const double dt,
                                const size_t steps);
