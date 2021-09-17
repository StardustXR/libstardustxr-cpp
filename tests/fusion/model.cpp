#include "fusion/fusion.hpp"
#include "fusion/types/model.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	Model model("../../../res/stardust_icon.glb", vec3_zero, quat_identity, vec3_one);
	StardustXRFusion::StallMainThread();
}
