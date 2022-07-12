#include "../../flex.hpp"
#include "../../fusion_internal.hpp"

#include "spatial.hpp"
#include "values.hpp"

namespace StardustXRFusion {

Spatial::Spatial() : Node() {
  this->core->name = "";
  this->core->path = "";
}

Spatial::Spatial(Spatial *parent, Vec3 origin, Quat rotation, Vec3 scale,
                 bool translatable, bool rotatable, bool scalable,
                 bool zoneable)
    : Node() {
  core->path = "/spatial/spatial";
  core->name = GenerateID();
  messenger->sendSignal(
      "/spatial", "createSpatial",
      FLEX_ARGS(FLEX_STRING(core->name) FLEX_STRING(
          parent ? parent->getNodePath() : std::string("")) FLEX_VEC3(origin)
                    FLEX_QUAT(rotation) FLEX_VEC3(scale) FLEX_BOOL(translatable)
                        FLEX_BOOL(rotatable) FLEX_BOOL(scalable)
                            FLEX_BOOL(zoneable)));
}

void Spatial::createLaunchAnchor(std::function<void(uint32_t)> callback) {
  executeMethod(
      "createLaunchAnchor", FLEX_ARG(FLEX_NULL),
      [callback](flexbuffers::Reference data) { callback(data.AsUInt32()); });
}

void Spatial::setOrigin(Vec3 origin, Spatial &space) {
  sendSignal("setTransform",
             FLEX_ARGS(FLEX_STRING(space.getNodePath()) FLEX_VEC3(origin)
                           FLEX_NULL FLEX_NULL));
}
void Spatial::setOrigin(Vec3 origin) {
  messenger->sendSignal(
      getNodePath().c_str(), "setTransform",
      FLEX_ARGS(FLEX_NULL FLEX_VEC3(origin) FLEX_NULL FLEX_NULL));
}

void Spatial::setOrientation(Quat rotation, Spatial &space) {
  sendSignal("setTransform",
             FLEX_ARGS(FLEX_STRING(space.getNodePath())
                           FLEX_NULL FLEX_QUAT(rotation) FLEX_NULL));
}
void Spatial::setOrientation(Quat rotation) {
  messenger->sendSignal(
      getNodePath().c_str(), "setTransform",
      FLEX_ARGS(FLEX_NULL FLEX_NULL FLEX_QUAT(rotation) FLEX_NULL));
}

void Spatial::setPose(Pose pose, Spatial &space) {
  sendSignal("setTransform",
             FLEX_ARGS(FLEX_STRING(space.getNodePath()) FLEX_VEC3(pose.position)
                           FLEX_QUAT(pose.rotation) FLEX_NULL));
}
void Spatial::setPose(Pose pose) {
  sendSignal("setTransform", FLEX_ARGS(FLEX_NULL FLEX_VEC3(pose.position)
                                           FLEX_QUAT(pose.rotation) FLEX_NULL));
}

void Spatial::setScale(Vec3 scale) {
  messenger->sendSignal(
      getNodePath().c_str(), "setTransform",
      FLEX_ARGS(FLEX_STRING("") FLEX_NULL FLEX_NULL FLEX_VEC3(scale)));
}

void Spatial::getTransform(Spatial *space,
                           std::function<void(Vec3, Quat, Vec3)> callback) {
  executeMethod(
      "getTransform",
      FLEX_ARG(FLEX_STRING(space ? space->getNodePath() : std::string(""))),
      [callback](flexbuffers::Reference data) {
        flexbuffers::Vector vec = data.AsVector();
        callback(STARDUST_VEC3(vec[0].AsTypedVector()),
                 STARDUST_QUAT(vec[1].AsTypedVector()),
                 STARDUST_VEC3(vec[2].AsTypedVector()));
      });
}

void Spatial::setSpatialParent(Spatial *space) {
  sendSignal(
      "setSpatialParent",
      FLEX_ARG(FLEX_STRING(space ? space->getNodePath() : std::string(""))));
}

void Spatial::setSpatialParentInPlace(Spatial *space) {
  sendSignal(
      "setSpatialParentInPlace",
      FLEX_ARG(FLEX_STRING(space ? space->getNodePath() : std::string(""))));
}

void Spatial::setZoneable(bool zoneable) {
  sendSignal("setZoneable", FLEX_ARG(FLEX_BOOL(zoneable)));
}

} // namespace StardustXRFusion
