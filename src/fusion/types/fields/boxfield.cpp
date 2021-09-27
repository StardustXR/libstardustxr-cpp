#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "boxfield.hpp"

namespace StardustXRFusion {

BoxField::BoxField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size) : Field(parent, origin, orientation) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createBoxField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(size)
		)
	);
}

void BoxField::setSize(SKMath::vec3 size) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setSize",
		FLEX_ARG(
			FLEX_VEC3(size)
		)
	);
}

} // namespace StardustXRFusion
