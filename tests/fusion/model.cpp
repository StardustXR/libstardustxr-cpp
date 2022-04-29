#include "fusion/fusion.hpp"
#include "fusion/types/drawable/model.hpp"
#include "values.hpp"

using namespace StardustXRFusion;


int main(int, char *[]) {
	StardustXRFusion::Setup();
	Model model(nullptr, "../../res/stardust_icon.glb", Vec3::Zero, Quat::Identity, Vec3::One * 0.1f);
	StardustXRFusion::RunEventLoop();
}
