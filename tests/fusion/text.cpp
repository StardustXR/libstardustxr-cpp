#include <cmath>
#include <unistd.h>

#include "fusion/values/glm.hpp"
#include "fusion/fusion.hpp"
#include "fusion/types/drawable/text.hpp"

using namespace StardustXRFusion;


int main() {
	if(!Setup())
		return 0;

	Text text(Root(), "Stardust XR", .025f, Vec3::Zero, glm::quat(glm::vec3(0, 180, 0)), "", Text::Align::Center, Vec2{.5f, .1f}, Text::Fit::Wrap, Text::Align::Center, Color{0, 1, 0.454f, 1});

	double elapsed = 0;

	OnLogicStep([&](double delta, double) {
		elapsed += delta;

		text.setColor(fmod(elapsed, 2) > 1 ? Color::White : Color::Black);
	});

	RunEventLoop();
}
