#include <chrono>
#include <iostream>
#include <thread>

#include "fusion/fusion.hpp"
#include "fusion/types/model.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	Model model("../../../res/stardust_icon.glb", vec3_zero, quat_identity, vec3_one);
	std::this_thread::sleep_for(std::chrono::seconds(3600));
}
