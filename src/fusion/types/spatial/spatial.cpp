#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "sk_math.hpp"
#include "spatial.hpp"

using namespace SKMath;

namespace StardustXRFusion {

Spatial::Spatial(bool destroyable) : Node(destroyable) {}

Spatial::Spatial() : Node(false) {
	this->nodeName = "";
	this->nodePath = "";
}

Spatial::Spatial(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale, bool translatable, bool rotatable, bool scalable, bool zoneable) :
Node(true) {
	nodePath = "/spatial/spatial";
	nodeName = GenerateID();
	messenger->sendSignal(
		"/spatial",
		"createSpatial",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(scale)
			FLEX_BOOL(translatable)
			FLEX_BOOL(rotatable)
			FLEX_BOOL(scalable)
			FLEX_BOOL(zoneable)
		)
	);
	return spatial;
}

void Spatial::setOrigin(vec3 origin, Spatial &space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_STRING(space.getNodePath())
			FLEX_VEC3(origin)
			FLEX_NULL
			FLEX_NULL
		)
	);
}
void Spatial::setOrigin(vec3 origin) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_NULL
			FLEX_VEC3(origin)
			FLEX_NULL
			FLEX_NULL
		)
	);
}

void Spatial::setOrientation(quat orientation, Spatial &space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_STRING(space.getNodePath())
			FLEX_NULL
			FLEX_QUAT(orientation)
			FLEX_NULL
		)
	);
}
void Spatial::setOrientation(quat orientation) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_NULL
			FLEX_NULL
			FLEX_QUAT(orientation)
			FLEX_NULL
		)
	);
}

void Spatial::setPose(pose_t pose, Spatial &space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_STRING(space.getNodePath())
			FLEX_VEC3(pose.position)
			FLEX_QUAT(pose.orientation)
			FLEX_NULL
		)
	);
}
void Spatial::setPose(pose_t pose) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_NULL
			FLEX_VEC3(pose.position)
			FLEX_QUAT(pose.orientation)
			FLEX_NULL
		)
	);
}

void Spatial::setScale(SKMath::vec3 scale) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_STRING("")
			FLEX_NULL
			FLEX_NULL
			FLEX_VEC3(scale)
		)
	);
}

void Spatial::getTransform(Spatial *space, std::function<void(SKMath::vec3, SKMath::quat, SKMath::vec3)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"getTransform",
		FLEX_ARG(FLEX_STRING(space ? space->getNodePath() : std::string(""))),
		[callback](flexbuffers::Reference data) {
			flexbuffers::Vector vec = data.AsVector();
			callback(SK_VEC3(vec[0].AsTypedVector()), SK_QUAT(vec[1].AsTypedVector()), SK_VEC3(vec[2].AsTypedVector()));
		}
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

void Spatial::setSpatialParentInPlace(Spatial *space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setSpatialParentInPlace",
		FLEX_ARG(
			FLEX_STRING(space ? space->getNodePath() : std::string(""))
		)
	);
}

void Spatial::setZoneable(bool zoneable) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setZoneable",
		FLEX_ARG(
			FLEX_BOOL(zoneable)
		)
	);
}

} // namespace StardustXRFusion
