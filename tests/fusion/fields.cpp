#include "fusion/fusion.hpp"
#include "fusion/types/fields/spherefield.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	SphereField sphereField(vec3_zero, 0.5f);
}
