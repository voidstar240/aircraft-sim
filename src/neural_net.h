#pragma once
#include <string>
#include <vector>
#include <cstdint>

// Stores basic data about an aircraft
struct Aircraft {
    std::string name;
    double approach_speed;
    double wingspan;
    double mtow;
    bool has_jet_engine;

    Aircraft(std::string name, double approach_speed,
             double wingspan, double mtow, bool has_jet_engine) :
        name(name),
        approach_speed(approach_speed),
        wingspan(wingspan),
        mtow(mtow),
        has_jet_engine(has_jet_engine) {};
};

// trains the neural net based on a data set. Returns the weights
std::vector<double> train_classifier(const std::vector<Aircraft>& training_data,
                                     const std::vector<double> w_0,
                                     const double a,
                                     const uint32_t iterations);
