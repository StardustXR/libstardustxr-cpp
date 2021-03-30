#include "../../libstardustxr.hpp"
#include "../../flex.hpp"

#include "spherefield.hpp"

namespace StardustXRFusion {

SphereField::SphereField(SKMath::vec3 origin, float radius) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createSphereField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_VEC3(origin)
			FLEX_FLOAT(radius)
		)
	);
}

SphereField::~SphereField() {}

} // namespace StardustXRFusion
