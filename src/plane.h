#pragma once
#include <string>
#include <random>
#include "graph.h"

class Plane {
protected:
	double wait_time;

private:
	double pos, vel, distance, loiter_time;
	bool at_SCE;
	NodeID origin, destination;
	const Graph<std::string, double>& airport_network;

public:
	Plane(std::string to, std::string from, const Graph<std::string, double>& airport_net);
	virtual ~Plane() = default;

	void operate(double dt);
	double get_pos() const { return pos; }
	double get_vel() const { return vel; }
	double get_distance() const { return distance; }
	double get_loiter_time() const { return loiter_time; }
	void set_vel(double vel) { this->vel = vel; }
	void set_loiter_time(double time) { this->loiter_time = static_cast<double>(time > 0.0)*time; }
	double distance_to_SCE() const { return static_cast<double>(destination == 0)*(distance-pos); }
	virtual double time_on_ground() const = 0;
	virtual std::string plane_type() const { return "GA"; };
	static double draw_from_normal_dist(double mean, double stdev);
};