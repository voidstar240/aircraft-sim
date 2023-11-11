#include <iostream>
#include <vector>
#include <chrono>
#include "SDL2/SDL.h"
#include "graph.h"
#include "plane.h"
#include "atc.h"
#include "HW2_Visualizer.h"

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

	HW2_VIZ viz;

	while (true) {
		AA5915.operate(50.0);
		UA5236.operate(50.0);
		UA4465.operate(50.0);
		AA6240.operate(50.0);
		GA1.operate(50.0);
		GA2.operate(50.0);
		GA3.operate(50.0);
		atc.control_traffic();
		std::cout << "AA5915: pos: " << AA5915.get_pos() << std::endl;
		std::cout << "UA5236: pos: " << UA5236.get_pos() << std::endl;
		std::cout << "UA4465: pos: " << UA4465.get_pos() << std::endl;
		std::cout << "AA6240: pos: " << AA6240.get_pos() << std::endl;
		std::cout << "GA1:    pos: " << AA5915.get_pos() << std::endl;
		std::cout << "GA1:    pos: " << AA5915.get_pos() << std::endl;
		std::cout << "GA1:    pos: " << AA5915.get_pos() << std::endl;
		viz.visualize_plane(AA5915.plane_type(), AA5915.get_origin_id(), AA5915.get_destination_id(), AA5915.get_pos());
		viz.visualize_plane(UA5236.plane_type(), UA5236.get_origin_id(), UA5236.get_destination_id(), UA5236.get_pos());
		viz.visualize_plane(UA4465.plane_type(), UA4465.get_origin_id(), UA4465.get_destination_id(), UA4465.get_pos());
		viz.visualize_plane(AA6240.plane_type(), AA6240.get_origin_id(), AA6240.get_destination_id(), AA6240.get_pos());
		viz.visualize_plane(GA1.plane_type(), GA1.get_origin_id(), GA1.get_destination_id(), GA1.get_pos());
		viz.visualize_plane(GA2.plane_type(), GA2.get_origin_id(), GA2.get_destination_id(), GA2.get_pos());
		viz.visualize_plane(GA3.plane_type(), GA3.get_origin_id(), GA3.get_destination_id(), GA3.get_pos());
		if (!viz.update(50.0)) {
			break;
		}
	}

	return 0;
}