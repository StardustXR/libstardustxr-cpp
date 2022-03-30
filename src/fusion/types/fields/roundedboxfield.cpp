#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "roundedboxfield.hpp"
#include "types/fields/boxfield.hpp"

using namespace SKMath;

namespace StardustXRFusion {

RoundedBoxField::RoundedBoxField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createRoundedBoxField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(size)
		)
	);
}

} // namespace StardustXRFusion
