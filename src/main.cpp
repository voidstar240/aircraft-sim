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
#include "neural_net.h"

// 1 for -inf < x < 2, 0 otherwise
double pilot_aileron_deflection(const double time) {
    if (time <= 2) {
        return 1.0;
    } else {
        return 0.0;
    }
}

std::vector<double> pilot_roll_rate_dot(const double time,
                                        const double* state) {
    const double roll_damping = -0.8;
    const double aileron_eff = 0.9;
    const double p = state[0];

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * p + aileron_eff * pilot_aileron_deflection(time);
    return { roll_rate_dot };
}

double auto_aileron_deflection(const double* state) {
    const double k = 1.5;
    const double p = state[0];
    return -k * p;
}

std::vector<double> auto_roll_rate_dot(const double time, const double* state) {
    const double roll_damping = -0.8;
    const double aileron_eff = 0.9;
    const double p = state[0];

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * p + aileron_eff * auto_aileron_deflection(state);
    return { roll_rate_dot };
}

double auto_k_aileron_deflection(const double* state) {
    const double p = state[0];
    const double k = state[1];
    return -k * p;
}

// only use this with a forward euler integrator with dt = 0.01
std::vector<double> auto_k_roll_rate_dot(const double time,
                                         const double* state) {
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

// pretty prints the roll states
void pretty_print_roll_states(const IntegrationData* data) {
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

// prints roll states out in csv format so it can be graphed easily
void csv_print_roll_states(const IntegrationData* data) {
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
    IntegrationData data = euler_integrate(
            pilot_roll_rate_dot, { p_0 }, t_initial, delta_t, step_num
        );

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
    IntegrationData data = euler_integrate(
            auto_roll_rate_dot, { p_0 }, t_initial, delta_t, step_num
        );

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
    IntegrationData data = euler_integrate(
            auto_k_roll_rate_dot, { p_0, k_0 }, t_initial, delta_t, step_num
        );

    // print roll states
    pretty_print_roll_states(&data);
    // csv_print_roll_states(&data);

    std::cout << "\n" << std::endl;
}

void question_4() {
    std::cout << "==================\n";
    std::cout << "=== Question 4 ===\n";
    std::cout << "==================\n" << std::endl;

    // set w and x
    std::vector<double> w = { 0.0001, 0.0001, 0.0001 };
    std::vector<double> x = { 124, 31.89, 20.945 };

    // calc dot product of w and x
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

void question_6() {
    std::cout << "==================\n";
    std::cout << "=== Question 6 ===\n";
    std::cout << "==================\n" << std::endl;

    const double y = 1;
    const double y_pred = 0.504421;
    const double grad_cost = gradient_cost(y_pred, y);

    std::cout << "gradient_cost(0.504421, 1) = " << std::fixed
        << std::setprecision(6) << grad_cost << "\n\n" << std::endl;
}

void question_7() {
    std::cout << "==================\n";
    std::cout << "=== Question 7 ===\n";
    std::cout << "==================\n" << std::endl;

    const double y = 1;
    const std::vector<double> w = { 0.0001, 0.0001, 0.0001 };
    const std::vector<double> x = { 124, 31.89, 20.945 };
    const double a = 0.001;
    const std::vector<double> dw = gradient_weights(w, x, y);
    const std::vector<double> w_next = update_weights(w, dw, a);

    std::cout << "dw = [ ";
    std::cout << std::fixed << std::setprecision(7) << dw[0] << "; ";
    std::cout << std::fixed << std::setprecision(7) << dw[1] << "; ";
    std::cout << std::fixed << std::setprecision(7) << dw[2] << " ]\n";
    
    std::cout << "w = [ ";
    std::cout << std::fixed << std::setprecision(7) << w_next[0] << "; ";
    std::cout << std::fixed << std::setprecision(7) << w_next[1] << "; ";
    std::cout << std::fixed << std::setprecision(7) << w_next[2] << " ]\n";
    std::cout << "\n" << std::endl;
}

std::vector<double> question_8() {
    std::cout << "==================\n";
    std::cout << "=== Question 8 ===\n";
    std::cout << "==================\n" << std::endl;

    // create training data set
    const std::vector<Aircraft> aircraft_training_data = {
        Aircraft("M-346 Master",    124.0, 31.89, 20.945, true ),
        Aircraft("AT-402B",          74.0, 51.08,  9.170, false),
        Aircraft("MB-326",          103.0, 34.67,  8.300, true ),
        Aircraft("AT-502B",          77.0, 52.00,  9.400, false),
        Aircraft("MB-339",          104.0, 35.63, 13.000, true ),
        Aircraft("AT-602",           92.0, 56.00, 12.500, false),
        Aircraft("Aero L-159 Alca", 130.0, 31.29, 17.637, true ),
        Aircraft("AT-504",           73.0, 52.00,  9.600, false),
    };

    const std::vector<double> w_0 = { 0.0001, 0.0001, 0.0001 };
    const double a = 0.001;

    // train the neural net to obtain weights
    const std::vector<double> w =
        train_classifier(aircraft_training_data, w_0, a, 500);

    std::cout << "w = [ ";
    std::cout << std::fixed << std::setprecision(6) << w[0] << "; ";
    std::cout << std::fixed << std::setprecision(6) << w[1] << "; ";
    std::cout << std::fixed << std::setprecision(6) << w[2] << " ]\n";
    std::cout << "\n" << std::endl;

    // return weights so they don't have to be recalculated in question 9
    return w;
}

void question_9(const std::vector<double>& weights) {
    std::cout << "==================\n";
    std::cout << "=== Question 9 ===\n";
    std::cout << "==================\n" << std::endl;

    // predict the engine type of 4 new aircraft
    const bool vision = 0.5 > sigmoid(dot_product(weights,
                std::vector<double>{ 87.0, 38.67,  6.000 }));
    const bool caravan = 0.5 > sigmoid(dot_product(weights,
                std::vector<double>{ 79.0, 52.08,  8.000 }));
    const bool delfin = 0.5 > sigmoid(dot_product(weights,
                std::vector<double>{ 92.0, 33.75,  7.804 }));
    const bool at802u = 0.5 > sigmoid(dot_product(weights,
                std::vector<double>{ 91.0, 59.25, 16.000 }));

    std::cout << "Aircraft Classifications:\n";
    std::cout << "  SF50 Vision:      "
        << (vision ? "Jet" : "Turboprop") << "\n";
    std::cout << "  208 Caravan:      "
        << (caravan ? "Jet" : "Turboprop") << "\n";
    std::cout << "  Aero L-29 Delfin: "
        << (delfin ? "Jet" : "Turboprop") << "\n";
    std::cout << "  AT-802U:          "
        << (at802u ? "Jet" : "Turboprop") << "\n";
    std::cout << "\n" << std::endl;
}

int main() {
    question_1();
    question_2();
    question_3();
    question_4();
    question_5();
    question_6();
    question_7();
    const std::vector<double> w = question_8();
    question_9(w);
} 
