#include "../libstardustxr.hpp"
#include "../flex.hpp"

#include "spatialnode.hpp"

namespace StardustXRFusion {

SpatialNode::SpatialNode() {}
SpatialNode::~SpatialNode() {}

void SpatialNode::setOrigin(SKMath::vec3 origin) {
	StardustXRFusion::messenger->sendSignal(
		getNodePath().c_str(),
		"setOrigin",
		FLEX_ARG(
			FLEX_VEC3(origin)
		)
	);
}

void SpatialNode::setOrientation(SKMath::quat orientation) {
	StardustXRFusion::messenger->sendSignal(
		getNodePath().c_str(),
		"setOrientation",
		FLEX_ARG(
			FLEX_QUAT(orientation)
		)
	);
}

void SpatialNode::setScale(SKMath::vec3 scale) {
	StardustXRFusion::messenger->sendSignal(
		getNodePath().c_str(),
		"setScale",
		FLEX_ARG(
			FLEX_VEC3(scale)
		)
	);
}

void SpatialNode::setPose(SKMath::pose_t pose) {
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
