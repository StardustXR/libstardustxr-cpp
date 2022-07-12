#include "zone.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"
#include <flatbuffers/flexbuffers.h>

namespace StardustXRFusion {

Zone::Zone(Spatial *parent, Field &field, Vec3 origin, Quat rotation)
    : Spatial() {
  core->path = "/spatial/zone";
  core->name = GenerateID();

  core->methods[core->name] = std::bind(
      &Zone::updateZone, this, std::placeholders::_1, std::placeholders::_2);
  scenegraph->addNode(core);

  messenger->sendSignal(
      "/spatial", "createZone",
      FLEX_ARGS(
          FLEX_STRING(core->name) FLEX_STRING(field.getNodePath())
              FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
                  FLEX_VEC3(origin) FLEX_QUAT(rotation)
                      FLEX_STRING(std::string("")) FLEX_STRING(core->name)));
}
Zone::~Zone() {
  for (auto space : spatials) {
    release(space.second);
  }
}

void Zone::isCaptured(Spatial &spatial, std::function<void(bool)> callback) {
  executeMethod(
      "isCaptured", FLEX_ARG(FLEX_STRING(spatial.getNodeName())),
      [callback](flexbuffers::Reference data) { callback(data.AsBool()); });
}

void Zone::capture(Spatial &spatial) {
  sendSignal("capture", FLEX_ARG(FLEX_STRING(spatial.getNodeName())));
}

void Zone::release(Spatial &spatial) {
  sendSignal("release", FLEX_ARG(FLEX_STRING(spatial.getNodeName())));
}

std::vector<uint8_t> Zone::updateZone(flexbuffers::Reference data, bool) {
  flexbuffers::Vector vector = data.AsVector();
  flexbuffers::TypedVector enter = vector[0].AsTypedVector();
  flexbuffers::TypedVector exit = vector[1].AsTypedVector();

  for (uint i = 0; i < enter.size(); ++i) {
    std::string uuid = enter[i].AsString().str();
    Spatial spatial;
    spatial.setBackend(
        std::shared_ptr<NodeCore>(new NodeCore(getNodePath(), uuid, false)));
    spatials.emplace(uuid, spatial);
    onSpatialEnter(spatial);
  }
  for (uint i = 0; i < exit.size(); ++i) {
    std::string uuid = exit[i].AsString().str();
    spatials.erase(uuid);
    onSpatialLeave(uuid);
  }
  return std::vector<uint8_t>();
}

} // namespace StardustXRFusion
