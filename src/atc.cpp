#include "atc.h"

const int ATC::MAX_LANDED_PLANE_NUM = 2;
const int ATC::AIRSPACE_DISTANCE = 50;

void ATC::control_traffic()
{
	size_t landed_planes = 0;

	for (Plane* plane : registered_planes) {
		landed_planes += plane->get_at_SCE();
	}

	if (landed_planes < ATC::MAX_LANDED_PLANE_NUM) {
		return;
	}

	for (Plane* plane : registered_planes) {
		if (!plane->get_at_SCE() && (plane->distance_to_SCE() <= ATC::AIRSPACE_DISTANCE) && (plane->get_loiter_time() <= 0)) {
			plane->set_loiter_time(100);
		}
	}
}
