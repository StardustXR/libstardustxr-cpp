#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "sk_math.hpp"
#include "spatial.hpp"

using namespace SKMath;

namespace StardustXRFusion {

Spatial::Spatial(Spatial *parent, std::string nodePath, std::string nodeName) {
	this->parent = parent;
	this->nodePath = nodePath;
	this->nodeName = nodeName;
}

Spatial::Spatial(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale) {
	this->parent = parent;
	this->origin = origin;
	this->orientation = orientation;
	this->localScale = scale;
}

Spatial Spatial::create(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale, bool translatable, bool rotatable, bool scalable, bool zoneable) {
	Spatial spatial(parent, origin, orientation, scale);
	spatial.nodePath = "/spatial/spatial";
	spatial.nodeName = GenerateID();
	messenger->sendSignal(
		"/spatial",
		"createSpatial",
		FLEX_ARGS(
			FLEX_STRING(spatial.nodeName)
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

void Spatial::move(vec3 position) {
	origin = origin + position;
	messenger->sendSignal(
		getNodePath().c_str(),
		"move",
		FLEX_ARG(
			FLEX_VEC3(position)
		)
	);
}

void Spatial::rotate(quat rotation) {
	orientation = orientation * rotation;
	messenger->sendSignal(
		getNodePath().c_str(),
		"rotate",
		FLEX_ARG(
			FLEX_QUAT(rotation)
		)
	);
}

void Spatial::scale(float scaleFactor) {
	this->localScale *= scaleFactor;
	messenger->sendSignal(
		getNodePath().c_str(),
		"scale",
		FLEX_ARG(
			FLEX_FLOAT(scaleFactor)
		)
	);
}

void Spatial::setOrigin(vec3 origin) {
	this->origin = origin;
	messenger->sendSignal(
		getNodePath().c_str(),
		"setOrigin",
		FLEX_ARG(
			FLEX_VEC3(origin)
		)
	);
}

void Spatial::setOrientation(quat orientation) {
	this->orientation = orientation;
	messenger->sendSignal(
		getNodePath().c_str(),
		"setOrientation",
		FLEX_ARG(
			FLEX_QUAT(orientation)
		)
	);
}

void Spatial::setScale(vec3 scale) {
	localScale = scale;
	messenger->sendSignal(
		getNodePath().c_str(),
		"setScale",
		FLEX_ARG(
			FLEX_VEC3(scale)
		)
	);
}

void Spatial::setPose(pose_t pose) {
	origin = pose.position;
	orientation = pose.orientation;
	messenger->sendSignal(
		getNodePath().c_str(),
		"setPose",
		FLEX_ARGS(
			FLEX_VEC3(pose.position)
			FLEX_QUAT(pose.orientation)
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

Spatial *Spatial::getSpatialParent() {
	return parent;
}

void Spatial::setSpatialParent(Spatial *space) {
	parent = space;
	messenger->sendSignal(
		getNodePath().c_str(),
		"setSpatialParent",
		FLEX_ARG(
			FLEX_STRING(space ? space->getNodePath() : std::string(""))
		)
	);
}

void Spatial::setSpatialParentInPlace(Spatial *space) {
	parent = space;
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

SKMath::vec3 Spatial::getOrigin() {
	return origin;
}
SKMath::quat Spatial::getOrientation() {
	return orientation;
}
SKMath::vec3 Spatial::getScale() {
	return localScale;
}
SKMath::pose_t Spatial::getPose() {
	return pose_t{
		getOrigin(),
		getOrientation()
	};
}

} // namespace StardustXRFusion
