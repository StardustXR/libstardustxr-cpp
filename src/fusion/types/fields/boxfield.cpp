#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "boxfield.hpp"



namespace StardustXRFusion {

BoxField::BoxField(Spatial *parent, Vec3 origin, Quat rotation, Vec3 size) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createBoxField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_VEC3(size)
		)
	);
}

void BoxField::setSize(Vec3 size) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setSize",
		FLEX_ARG(
			FLEX_VEC3(size)
		)
	);
}

} // namespace StardustXRFusion
