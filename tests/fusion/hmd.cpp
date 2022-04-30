#include "fusion/fusion.hpp"
#include "fusion/types/drawable/model.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	if(!Setup())
		return 1;

	Model stardustIcon(HMD(), "../../res/stardust_icon.glb", Vec3::Forward * 1.5f);

	StardustXRFusion::RunEventLoop();
}
