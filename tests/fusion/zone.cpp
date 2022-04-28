#include "fusion/fusion.hpp"
#include "values.hpp"
#include "types/fields/spherefield.hpp"
#include "types/spatial/zone.hpp"

using namespace StardustXRFusion;


int main(int, char *[]) {
	StardustXRFusion::Setup();

	SphereField field(Root(), Vec3::Zero, 0.25f);
	Zone zone(Root(), field);

	zone.onSpatialEnter = [&zone](Spatial &spatial) {
		printf("%s entered ", spatial.getNodeName().c_str());
		zone.isCaptured(spatial, [](bool captured) {
			printf(captured ? "captured\n" : "uncaptured\n");
		});
		zone.capture(spatial);
	};
	zone.onSpatialLeave = [](std::string &uuid) {
		printf("%s left\n", uuid.c_str());
	};

	StardustXRFusion::RunEventLoop();
}
