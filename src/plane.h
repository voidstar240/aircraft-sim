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
	Plane(std::string from, std::string to, const Graph<std::string, double>& airport_net);
	virtual ~Plane() {}

	void operate(double dt);
	inline double get_pos() const { return pos; }
	inline double get_vel() const { return vel; }
	inline double get_loiter_time() const { return loiter_time; }
	inline std::string get_origin() const { return airport_network.get_node_data(origin); }
	inline std::string get_destination() const { return airport_network.get_node_data(destination); }
	inline bool get_at_SCE() const { return at_SCE; }
	inline void set_vel(double vel) { this->vel = vel; }
	inline void set_loiter_time(double time) { this->loiter_time = static_cast<double>(time > 0.0)*time; }
	inline double distance_to_SCE() const { return static_cast<double>(destination == 0)*(distance-pos); }
	virtual double time_on_ground() = 0;
	virtual std::string plane_type() const { return "GA"; };
	static double draw_from_normal_dist(double mean, double stdev);
};

class Airliner : public Plane {
	std::string Airline;

public:
	Airliner(std::string Airline, std::string from, std::string to, const Graph<std::string, double> airport_net) : Plane(from, to, airport_net), Airline(Airline) {}
	~Airliner() {}

	std::string plane_type() const override { return Airline; }
	double time_on_ground() override {
		this->wait_time = Plane::draw_from_normal_dist(1800, 600);
		return this->wait_time;
	}
};

class GeneralAviation : public Plane {
public:
	GeneralAviation(std::string to, std::string from, const Graph<std::string, double> airport_net) : Plane(from, to, airport_net) {}
	~GeneralAviation() {}

	double time_on_ground() override {
		this->wait_time = Plane::draw_from_normal_dist(600, 60);
		return this->wait_time;
	}
};