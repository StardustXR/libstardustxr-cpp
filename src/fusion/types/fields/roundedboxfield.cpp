#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "roundedboxfield.hpp"
#include "types/fields/boxfield.hpp"



namespace StardustXRFusion {

RoundedBoxField::RoundedBoxField(Spatial *parent, Vec3 origin, Quat rotation, Vec3 size) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createRoundedBoxField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_VEC3(size)
		)
	);
}

} // namespace StardustXRFusion
