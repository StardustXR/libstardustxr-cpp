#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "sk_math.hpp"
#include "spherefield.hpp"

namespace StardustXRFusion {

SphereField::SphereField(Spatial *parent, SKMath::vec3 origin, float radius) : Field(parent, origin, quat_identity) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createSphereField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_FLOAT(radius)
		)
	);
}

} // namespace StardustXRFusion
