#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "roundedboxfield.hpp"

namespace StardustXRFusion {

RoundedBoxField::RoundedBoxField(SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createRoundedBoxField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(size)
		)
	);
}

RoundedBoxField::~RoundedBoxField() {}

} // namespace StardustXRFusion
