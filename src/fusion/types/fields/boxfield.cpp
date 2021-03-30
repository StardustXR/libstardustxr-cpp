#include "../../libstardustxr.hpp"
#include "../../flex.hpp"

#include "boxfield.hpp"

namespace StardustXRFusion {

BoxField::BoxField(SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createBoxField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(size)
		)
	);
}

BoxField::~BoxField() {

}

} // namespace StardustXRFusion
