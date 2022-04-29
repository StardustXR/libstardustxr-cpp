#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "values.hpp"
#include "spherefield.hpp"



namespace StardustXRFusion {

SphereField::SphereField(Spatial *parent, Vec3 origin, float radius) {
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
