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
		Color gemColor = Color::FromHSVA(
			(float) (int(elapsed * 180) % 360),
			1,
			1,
			abs(sinf(elapsed))
		);
		model.setMaterialProperty(0, "color", gemColor);
	});
	StardustXRFusion::RunEventLoop();
}
