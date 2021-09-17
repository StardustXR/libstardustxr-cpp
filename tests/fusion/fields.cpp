#include "fusion/fusion.hpp"
#include "fusion/types/fields/spherefield.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	SphereField sphereField(vec3_zero, 0.5f);
	sphereField.distance(&sphereField, vec3_right*1.0f, [&](float distance) {
		printf("Distance: %f\n", distance);
	});
	StardustXRFusion::ShutdownAfterInput();
}
