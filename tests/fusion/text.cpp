#include <unistd.h>

#include "fusion/fusion.hpp"
#include "fusion/types/drawable/text.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main() {
	if(!Setup())
		return 0;

	Text text(Root(), "Stardust XR", .025f, vec3_zero, quat_from_angles(0, 180, 0), "", Text::Align::Center, vec2{.5f, .1f}, Text::Fit::Wrap, Text::Align::Center, color{0, 1, 0.454f, 1});

	pause();
	return 0;
}
