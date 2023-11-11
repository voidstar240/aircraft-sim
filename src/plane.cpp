#include "plane.h"
#include <stdexcept>
#include <sstream>

Plane::Plane(std::string to, std::string from, const Graph<std::string, double>& airport_net) : airport_network(airport_net)
{
	if (!this->airport_network.find_node_id(to, this->origin)) {
		std::stringstream err;
		err << "`airport_net` has no airport named " << to << std::endl;
		std::invalid_argument(err.str());
	}

	if (!this->airport_network.find_node_id(from, this->destination)) {
		std::stringstream err;
		err << "`airport_net` has no airport named " << to << std::endl;
		std::invalid_argument(err.str());
	}

	if (!this->airport_network.find_edge_between_nodes(this->origin, this->destination, this->distance)) {
		std::stringstream err;
		err << "`airport_net` has no edge connecting " << to << " to " << from << std::endl;
		std::invalid_argument(err.str());
	}

	this->pos = 0.0;
	this->vel = 0.0;
	this->wait_time = 0.0;
	this->loiter_time = 0.0;
	this->at_SCE = false;
}

void Plane::operate(double dt)
{
	if (this->loiter_time > 0) {
		this->loiter_time -= dt;
		return;
	}
	this->loiter_time = 0.0;

	if (this->wait_time > 0) {
		this->wait_time -= dt;
		return;
	}
	this->wait_time = 0.0;

	if (this->pos < this->distance) {
		pos += vel * dt;
		this->at_SCE = false;
		return;
	}

	if (this->destination == 0) {
		this->at_SCE = this;
	}

	time_on_ground();
	NodeID temp = this->origin;
	this->origin = this->destination;
	this->destination = temp;
	this->pos = 0.0;
}

double Plane::draw_from_normal_dist(double mean, double stdev)
{
	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<> d{ mean, stdev };
	return d(gen);
}
