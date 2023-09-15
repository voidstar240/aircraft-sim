#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

struct RollState {
    double time;
    double roll_rate;

    RollState(double time, double roll_rate) : time(time), roll_rate(roll_rate) {}
    RollState() : time(0.0), roll_rate(0.0) {}
};

typedef double (*AileronDefFunc)(RollState);
typedef double (*RollRateDotFunc)(RollState);

double pilot_aileron_deflection(RollState state) {
    if (state.time <= 2) {
        return 1.0;
    } else {
        return 0.0;
    }
}

double pilot_roll_rate_dot(RollState state) {
    const double roll_damping = -0.8;
    const double aileron_eff = 0.9;

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * state.roll_rate + aileron_eff * pilot_aileron_deflection(state);
    return roll_rate_dot;
}

double auto_aileron_deflection(RollState state) {
    const double k = 1.5;
    return -k * state.roll_rate;
}

double auto_roll_rate_dot(RollState state) {
    const double roll_damping = -0.8;
    const double aileron_eff = 0.9;

    // p_dot = L_p * p + L_del * delta
    const double roll_rate_dot =
          roll_damping * state.roll_rate + aileron_eff * auto_aileron_deflection(state);
    return roll_rate_dot;
}

void roll_rate_prediction(RollRateDotFunc roll_rate_dot,
                              std::vector<RollState> &states, double dt) {
    for (size_t i = 0; i < states.size() - 1; i++) {
        const RollState cur_state = states[i]; // p_0

        // p_t+1 = p_t + p_t_dot * dt
        const double next_roll_rate =
            cur_state.roll_rate + roll_rate_dot(cur_state) * dt;
        const double next_time = dt * static_cast<double>(i + 1);
        const RollState next_roll_state = RollState(next_time, next_roll_rate);

        states[i + 1] = next_roll_state;
    }
}

void pretty_print_roll_states(std::vector<RollState> roll_states) {
    std::cout << "+--------+-----------+\n";
    std::cout << "|  Time  | Roll Rate |\n";
    std::cout << "+--------+-----------+\n";
    for (RollState state : roll_states) {
        std::cout << "| " << std::fixed << std::setprecision(2) << std::setw(6)
                  << state.time << " | " << std::fixed << std::setprecision(3)
                  << std::setw(9) << state.roll_rate << " |\n";
    }
    std::cout << "+--------+-----------+" << std::endl;
}

void csv_print_roll_states(std::vector<RollState> roll_states) {
    std::cout << "time,roll rate\n";
    for (RollState state : roll_states) {
        std::cout << state.time << "," << state.roll_rate << "\n";
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

    // set up initial conditions
    std::vector<RollState> roll_states = std::vector(step_num, RollState());
    roll_states[0] = RollState(0.0, 1.0);

    // integrate
    roll_rate_prediction(pilot_roll_rate_dot, roll_states, delta_t);

    // print roll states
    pretty_print_roll_states(roll_states);
    // csv_print_roll_states(roll_states);

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

    // set up initial conditions
    std::vector<RollState> roll_states = std::vector(step_num, RollState());
    roll_states[0] = RollState(0.0, 1.0);

    // integrate
    roll_rate_prediction(auto_roll_rate_dot, roll_states, delta_t);

    // print roll states
    pretty_print_roll_states(roll_states);
    // csv_print_roll_states(roll_states);

    std::cout << "\n" << std::endl;
}

int main() {
    question_1();
    question_2();
}
