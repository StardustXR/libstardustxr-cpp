#include "fusion/fusion.hpp"
#include "fusion/types/fields/spherefield.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	SphereField sphereField(nullptr, Vec3::Zero, 0.5f);
	sphereField.distance(&sphereField, Vec3::Right*1.0f, [&](float distance) {
		printf("Distance: %f\n", distance);
	});
	StardustXRFusion::RunEventLoop();
}
