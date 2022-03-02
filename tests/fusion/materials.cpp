#include <cmath>

#include "fusion/fusion.hpp"
#include "fusion/types/drawable/model.hpp"

using namespace StardustXRFusion;

double elapsed = 0.0f;

int main(int, char *[]) {
	StardustXRFusion::Setup();
	Model model(nullptr, "../../../res/gyro_gem.glb");
	OnLogicStep([&](double delta, double) {
		elapsed += delta;
		SKMath::color gemColor = SKMath::color_from_hsva(
			(float) (int(elapsed * 180) % 360),
			1,
			1,
			abs(sinf(elapsed))
		);
		model.setMaterialProperty(0, "color", gemColor);
	});
	StardustXRFusion::StallMainThread();
}
