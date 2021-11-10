#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "cylinderfield.hpp"

using namespace SKMath;

namespace StardustXRFusion {

CylinderField::CylinderField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, float length, float radius) : Field(parent, origin, orientation) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createCylinderField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_FLOAT(length)
			FLEX_FLOAT(radius)
		)
	);
}

} // namespace StardustXRFusion
