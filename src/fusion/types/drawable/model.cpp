#include "model.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"

namespace StardustXRFusion {

Model::Model(Spatial *parent, std::string relativePath, Vec3 origin,
             Quat rotation, Vec3 scale)
    : Spatial() {
  if (!FileExists(relativePath))
    return;
  core->path = "/drawable/model";
  core->name = GenerateID();

  messenger->sendSignal(
      "/drawable", "createModelFromFile",
      FLEX_ARGS(
          FLEX_STRING(core->name)
              FLEX_STRING(ConvertExeRelativePath(relativePath))
                  FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
                      FLEX_VEC3(origin) FLEX_QUAT(rotation) FLEX_VEC3(scale)));
  valid = true;
}

void Model::setMaterialProperty(uint32_t submesh, std::string propertyName,
                                float value) {
  messenger->sendSignal(
      getNodePath().c_str(), "setMaterialProperty",
      FLEX_ARGS(FLEX_ADD(submesh) FLEX_STRING(propertyName) FLEX_FLOAT(value)));
}

void Model::setMaterialProperty(uint32_t submesh, std::string propertyName,
                                Color color) {
  messenger->sendSignal(
      getNodePath().c_str(), "setMaterialProperty",
      FLEX_ARGS(FLEX_ADD(submesh) FLEX_STRING(propertyName) FLEX_COLOR(color)));
}

void Model::setMaterialProperty(uint32_t submesh, std::string propertyName,
                                std::string value) {
  if (!FileExists(value))
    return;
  messenger->sendSignal(
      getNodePath().c_str(), "setMaterialProperty",
      FLEX_ARGS(FLEX_ADD(submesh) FLEX_STRING(propertyName)
                    FLEX_STRING(ConvertExeRelativePath(value))));
}

} // namespace StardustXRFusion
