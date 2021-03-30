#include "../libstardustxr.hpp"
#include "../flex.hpp"

#include "spatial.hpp"

namespace StardustXRFusion {

Spatial::Spatial() {}
Spatial::~Spatial() {}

void Spatial::setOrigin(SKMath::vec3 origin) {
	StardustXRFusion::messenger->sendSignal(
		getNodePath().c_str(),
		"setOrigin",
		FLEX_ARG(
			FLEX_VEC3(origin)
		)
	);
}

void Spatial::setOrientation(SKMath::quat orientation) {
	StardustXRFusion::messenger->sendSignal(
		getNodePath().c_str(),
		"setOrientation",
		FLEX_ARG(
			FLEX_QUAT(orientation)
		)
	);
}

void Spatial::setScale(SKMath::vec3 scale) {
	StardustXRFusion::messenger->sendSignal(
		getNodePath().c_str(),
		"setScale",
		FLEX_ARG(
			FLEX_VEC3(scale)
		)
	);
}

void Spatial::setPose(SKMath::pose_t pose) {
	StardustXRFusion::messenger->sendSignal(
		getNodePath().c_str(),
		"setPose",
		FLEX_ARGS(
			FLEX_VEC3(pose.position)
			FLEX_QUAT(pose.orientation)
		)
	);
}

} // namespace StardustXRFusion
