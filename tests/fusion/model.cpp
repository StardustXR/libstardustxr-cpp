#include "fusion/fusion.hpp"
#include "fusion/types/drawable/model.hpp"
#include "sk_math.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	Model model(nullptr, "../../../res/stardust_icon.glb", vec3_zero, quat_identity, vec3_one * 0.1f);
	StardustXRFusion::StallMainThread();
}
