#pragma once

#include "../../../sk_math.hpp"

namespace StardustXR {
	class InputData;
}

namespace StardustXRFusion {

class PointerInput {
public:
	explicit PointerInput(const StardustXR::InputData *pointer);

	const float distance;

	const SKMath::vec3 origin;
	const SKMath::vec3 direction;
	const float tilt = 0.0f;
};

} // namespace StardustXRFusion
