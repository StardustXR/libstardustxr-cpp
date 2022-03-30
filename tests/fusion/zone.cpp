#include "fusion/fusion.hpp"
#include "sk_math.hpp"
#include "types/fields/spherefield.hpp"
#include "types/spatial/zone.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();

	SphereField field(Root(), vec3_zero, 0.25f);
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

	StardustXRFusion::StallMainThread();
}
