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
#include "math_funcs.h"

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
    const double p = state[0];

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * p + aileron_eff * pilot_aileron_deflection(time);
    return { roll_rate_dot };
}

double auto_aileron_deflection(double* state) {
    const double k = 1.5;
    const double p = state[0];
    return -k * p;
}

std::vector<double> auto_roll_rate_dot(double time, double* state) {
    const double roll_damping = -0.8;
    const double aileron_eff = 0.9;
    const double p = state[0];

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * p + aileron_eff * auto_aileron_deflection(state);
    return { roll_rate_dot };
}

double auto_k_aileron_deflection(double* state) {
    const double p = state[0];
    const double k = state[1];
    return -k * p;
}

// only use this with a forward euler integrator with dt = 0.01
std::vector<double> auto_k_roll_rate_dot(double time, double* state) {
    const double roll_damping = -0.8;
    const double aileron_eff = 0.9;
    const double alpha = 1.0;
    const double p = state[0];

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * p + aileron_eff * auto_k_aileron_deflection(state);
    const double k_dot = alpha * p * p / 0.01; // this is a horrible hack and
                                               // only works for a time step of
                                               // 0.01 in a forward Euler
                                               // integrator.
    return { roll_rate_dot, k_dot };
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

    const double p_0 = 1.0;

    // integrate
    IntegrationData data = euler_integrate(pilot_roll_rate_dot, { p_0 }, t_initial, delta_t, step_num);

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

    const double p_0 = 1.0;

    // integrate
    IntegrationData data = euler_integrate(auto_roll_rate_dot, { p_0 }, t_initial, delta_t, step_num);

    // print roll states
    pretty_print_roll_states(&data);
    // csv_print_roll_states(&data);

    std::cout << "\n" << std::endl;
}

void question_3() {
    std::cout << "==================\n";
    std::cout << "=== Question 3 ===\n";
    std::cout << "==================\n" << std::endl;

    // calc integration bounds
    const double t_initial = 0.0;
    const double t_final = 5.0;
    const double delta_t = 0.01;
    const uint64_t step_num = std::ceil(1.0 + (t_final - t_initial) / delta_t);

    const double p_0 = 1.0;
    const double k_0 = 1.5;

    // integrate
    IntegrationData data = euler_integrate(auto_k_roll_rate_dot, { p_0, k_0 }, t_initial, delta_t, step_num);

    // print roll states
    pretty_print_roll_states(&data);
    // csv_print_roll_states(&data);

    std::cout << "\n" << std::endl;
}

void question_4() {
    std::cout << "==================\n";
    std::cout << "=== Question 4 ===\n";
    std::cout << "==================\n" << std::endl;

    std::vector<double> w = { 0.0001, 0.0001, 0.0001 };
    std::vector<double> x = { 124, 31.89, 20.945 };
    double res = dot_product(w, x);

    std::cout << "z = wx = " << std::fixed << std::setprecision(7) << res
        << "\n\n" << std::endl;
}

void question_5() {
    std::cout << "==================\n";
    std::cout << "=== Question 5 ===\n";
    std::cout << "==================\n" << std::endl;

    const double z = 0.0176835;
    const double sig = sigmoid(z);
    const double grad_sig = gradient_sigmoid(z);

    std::cout << "sigmoid(0.0176835) = " << std::fixed << std::setprecision(6)
        << sig << "\ngradient_sigmoid(0.0176835) = " << grad_sig
        << "\n\n" << std::endl;
}

int main() {
    question_1();
    question_2();
    question_3();
    question_4();
    question_5();
} 
