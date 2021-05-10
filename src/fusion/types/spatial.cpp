#include "../fusion_internal.hpp"
#include "../flex.hpp"

#include "spatial.hpp"

using namespace SKMath;

namespace StardustXRFusion {

Spatial::Spatial() {}

Spatial::~Spatial() {}

Spatial Spatial::create(SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale, bool translatable, bool rotatable, bool scalable) {
	Spatial spatial;
	spatial.nodePath = "/spatial";
	spatial.nodeName = GenerateID();
	messenger->sendSignal(
		"/spatial",
		"create",
		FLEX_ARGS(
			FLEX_STRING(spatial.nodeName)
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(scale)
			FLEX_BOOL(translatable)
			FLEX_BOOL(rotatable)
			FLEX_BOOL(scalable)
		)
	);
	return spatial;
}

void Spatial::move(vec3 position) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"move",
		FLEX_ARG(
			FLEX_VEC3(position)
		)
	);
}

void Spatial::rotate(quat rotation) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"rotate",
		FLEX_ARG(
			FLEX_QUAT(rotation)
		)
	);
}

void Spatial::rotateAround(vec3 point, quat rotation) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"rotateAround",
		FLEX_ARGS(
			FLEX_VEC3(point)
			FLEX_QUAT(rotation)
		)
	);
}

void Spatial::scale(float scaleFactor) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"scale",
		FLEX_ARG(
			FLEX_FLOAT(scaleFactor)
		)
	);
}

void Spatial::setOrigin(vec3 origin) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setOrigin",
		FLEX_ARG(
			FLEX_VEC3(origin)
		)
	);
}

void Spatial::setOrientation(quat orientation) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setOrientation",
		FLEX_ARG(
			FLEX_QUAT(orientation)
		)
	);
}

void Spatial::setScale(vec3 scale) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setScale",
		FLEX_ARG(
			FLEX_VEC3(scale)
		)
	);
}

void Spatial::setPose(pose_t pose) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setPose",
		FLEX_ARGS(
			FLEX_VEC3(pose.position)
			FLEX_QUAT(pose.orientation)
		)
	);
}

void Spatial::setSpatialParent(Spatial *space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setSpatialParent",
		FLEX_ARG(
			FLEX_STRING(space ? space->getNodePath() : std::string(""))
		)
	);
}

} // namespace StardustXRFusion
