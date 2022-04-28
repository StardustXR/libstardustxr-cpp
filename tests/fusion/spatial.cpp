#include <cmath>

#include "fusion/values/glm.hpp"
#include "fusion/fusion.hpp"
#include "fusion/types/drawable/model.hpp"

using namespace StardustXRFusion;

int main(int, char *[]) {
	StardustXRFusion::Setup();

	double time = 0;
	double rotationSeconds = 5;

	StardustXRFusion::Root()->setZoneable(true);
	Spatial gyroRoot(StardustXRFusion::Root());
	Model outsideRing(&gyroRoot, "../../../res/gyro_outside.glb");
	Model middleRing(&outsideRing, "../../../res/gyro_middle.glb");
	Model insideRing(&middleRing, "../../../res/gyro_inside.glb");
	Model gem(&gyroRoot, "../../../res/gyro_gem.glb");

	OnLogicStep([&](double delta, double) {
		time += delta;
		double rotation = 360*time/rotationSeconds;

		gyroRoot.setOrigin(Vec3::Up * std::sin(glm::degrees(rotation)) * 0.1f);
		gem.setScale(Vec3::One * (1.0f + std::sin(glm::degrees(rotation*2)) * 0.25f));

		outsideRing.setOrientation(glm::quat(glm::vec3(rotation, 0, 0)));
		middleRing.setOrientation (glm::quat(glm::vec3(0, 0, rotation)));
		insideRing.setOrientation (glm::quat(glm::vec3(rotation, 0, 0)));
	});
	StardustXRFusion::RunEventLoop();
}
