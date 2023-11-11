#include <iostream>
#include <vector>
#include <chrono>
#include "SDL2/SDL.h"
#include "graph.h"
#include "plane.h"
#include "atc.h"

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

	ATC atc;
	atc.register_plane(AA5915);
	atc.register_plane(UA5236);
	atc.register_plane(UA4465);
	atc.register_plane(AA6240);
	atc.register_plane(GA1);
	atc.register_plane(GA2);
	atc.register_plane(GA3);

	while (true) {
		AA5915.operate(50);
		UA5236.operate(50);
		UA4465.operate(50);
		AA6240.operate(50);
		GA1.operate(50);
		GA2.operate(50);
		GA3.operate(50);
		atc.control_traffic();
		std::cout << "AA5915: pos: " << AA5915.get_pos() << std::endl;
		std::cout << "UA5236: pos: " << UA5236.get_pos() << std::endl;
		std::cout << "UA4465: pos: " << UA4465.get_pos() << std::endl;
		std::cout << "AA6240: pos: " << AA6240.get_pos() << std::endl;
		std::cout << "GA1:    pos: " << AA5915.get_pos() << std::endl;
		std::cout << "GA1:    pos: " << AA5915.get_pos() << std::endl;
		std::cout << "GA1:    pos: " << AA5915.get_pos() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}