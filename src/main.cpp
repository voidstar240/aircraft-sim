#include <iostream>
#include <vector>
#include <chrono>
#include "SDL2/SDL.h"
#include "graph.h"
#include "plane.h"

typedef std::string AirportName;
typedef double Distance;

int main(int argc, char* argv[]) {

	Graph<AirportName, Distance> airport_network = { "SCE", "PHL", "EWR", "ORD" };
	airport_network.add_non_directional_edge(0, 1, 160.0);
	airport_network.add_non_directional_edge(0, 2, 220.0);
	airport_network.add_non_directional_edge(0, 3, 640.0);

	Airliner AA5915 = Airliner("AA", "SCE", "PHL", airport_network);
	AA5915.set_vel(470.0 / 3600.0);
	Airliner UA5236 = Airliner("UA", "SCE", "ORD", airport_network);
	UA5236.set_vel(515.0 / 3600.0);
	Airliner UA4465 = Airliner("UA", "SCE", "EWR", airport_network);
	UA4465.set_vel(480.0 / 3600.0);
	Airliner AA6240 = Airliner("AA", "SCE", "ORD", airport_network);
	AA6240.set_vel(500.0 / 3600.0);
	
	GeneralAviation GA1 = GeneralAviation("SCE", "PHL", airport_network);
	GA1.set_vel(140.0 / 3600.0);
	GeneralAviation GA2 = GeneralAviation("SCE", "EWR", airport_network);
	GA2.set_vel(160.0 / 3600.0);
	GeneralAviation GA3 = GeneralAviation("SCE", "ORD", airport_network);
	GA3.set_vel(180.0 / 3600.0);

	while (true) {
		AA5915.operate(50);
		std::cout << AA5915.get_pos() << " " << *(reinterpret_cast<double*>(&AA5915) + 1) << " " <<  AA5915.distance_to_SCE() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}