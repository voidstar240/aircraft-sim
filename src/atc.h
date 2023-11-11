#pragma once
#include <vector>
#include "plane.h"

class ATC {
	std::vector<Plane*> registered_planes;
	static const int MAX_LANDED_PLANE_NUM;
	static const int AIRSPACE_DISTANCE;

public:
	ATC() {}
	~ATC() {}

	inline void register_plane(Plane& plane) {
		this->registered_planes.push_back(&plane);
	}

	void control_traffic();
};