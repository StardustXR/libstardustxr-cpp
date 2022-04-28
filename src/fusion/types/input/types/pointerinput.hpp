#pragma once

#include "../../../values.hpp"

namespace StardustXR {
	class InputData;
}

namespace StardustXRFusion {

class PointerInput {
public:
	explicit PointerInput(const StardustXR::InputData *pointer);

	const float distance;

	const Vec3 origin;
	const Vec3 direction;
	const float tilt = 0.0f;

	const Vec3 deepestPoint;
};

} // namespace StardustXRFusion
