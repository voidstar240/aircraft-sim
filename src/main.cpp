#include <iostream>
#include <vector>
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

	double dist_sce_ord = 0.0;
	if (airport_network.find_edge_between_nodes(3, 0, dist_sce_ord)) {
		std::cout << "Distance from ORD to SCE is " << dist_sce_ord << " miles." << std::endl;
	} else {
		std::cout << "No edge from ORD to SCE." << std::endl;
	}

	return 0;
}