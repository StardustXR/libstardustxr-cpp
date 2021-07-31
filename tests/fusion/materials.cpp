#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <thread>

#include "fusion/fusion.hpp"
#include "fusion/types/model.hpp"

using namespace StardustXRFusion;

double elapsed = 0.0f;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	Model model("../../../res/gyro_gem.glb");
	LifeCycle()->onLogicStep([&](double delta, double) {
		elapsed += delta;
		SKMath::color gemColor = SKMath::color_from_hsva(
			(float) (int(elapsed * 180) % 360),
			1,
			1,
			abs(sinf(elapsed))
		);
		model.setMaterialProperty(0, "color", gemColor);
	});
	std::this_thread::sleep_for(std::chrono::seconds(3600));
}
