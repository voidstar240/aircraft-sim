#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include "integrator.h"

double pilot_aileron_deflection(double time) {
    if (time <= 2) {
        return 1.0;
    } else {
        return 0.0;
    }
}

std::vector<double> pilot_roll_rate_dot(double time, double* state) {
    const double roll_damping = -0.8;
    const double aileron_eff = 0.9;

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * state[0] + aileron_eff * pilot_aileron_deflection(time);
    return { roll_rate_dot };
}

double auto_aileron_deflection(double* state) {
    const double k = 1.5;
    return -k * state[0];
}

std::vector<double> auto_roll_rate_dot(double time, double* state) {
    const double roll_damping = -0.8;
    const double aileron_eff = 0.9;

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * state[0] + aileron_eff * auto_aileron_deflection(state);
    return { roll_rate_dot };
}

void pretty_print_roll_states(IntegrationData* data) {
    std::cout << "+--------+-----------+\n";
    std::cout << "|  Time  | Roll Rate |\n";
    std::cout << "+--------+-----------+\n";
    for (int i = 0; i < data->get_steps(); i++) {
        std::cout << "| " << std::fixed << std::setprecision(2) << std::setw(6)
                  << data->get_time(i) << " | " << std::fixed << std::setprecision(3)
                  << std::setw(9) << data->get_state(i)[0] << " |\n";
    }
    std::cout << "+--------+-----------+" << std::endl;
}

void csv_print_roll_states(IntegrationData* data) {
    std::cout << "time,roll rate\n";
    for (int i = 0; i < data->get_steps(); i++) {
        std::cout << data->get_time(i) << "," << data->get_state(i)[0] << "\n";
    }
    std::cout << std::endl;
}

void question_1() {
    std::cout << "==================\n";
    std::cout << "=== Question 1 ===\n";
    std::cout << "==================\n" << std::endl;

    // calc integration bounds
    const double t_initial = 0.0;
    const double t_final = 5.0;
    const double delta_t = 0.01;
    const uint64_t step_num = std::ceil(1.0 + (t_final - t_initial) / delta_t);

    // integrate
    IntegrationData data = euler_integrate(pilot_roll_rate_dot, { 1.0 }, t_initial, delta_t, step_num);

    // print roll states
    pretty_print_roll_states(&data);
    // csv_print_roll_states(&data);

    std::cout << "\n" << std::endl;
}

void question_2() {
    std::cout << "==================\n";
    std::cout << "=== Question 2 ===\n";
    std::cout << "==================\n" << std::endl;

    // calc integration bounds
    const double t_initial = 0.0;
    const double t_final = 5.0;
    const double delta_t = 0.01;
    const uint64_t step_num = std::ceil(1.0 + (t_final - t_initial) / delta_t);

    // integrate
    IntegrationData data = euler_integrate(auto_roll_rate_dot, { 1.0 }, t_initial, delta_t, step_num);

    // print roll states
    pretty_print_roll_states(&data);
    // csv_print_roll_states(&data);

    std::cout << "\n" << std::endl;
}

int main() {
    question_1();
    question_2();
} 
