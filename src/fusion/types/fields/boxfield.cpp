#include "../../flex.hpp"
#include "../../fusion_internal.hpp"

#include "boxfield.hpp"

namespace StardustXRFusion {

BoxField::BoxField(Spatial *parent, Vec3 origin, Quat rotation, Vec3 size) {
  core->name = GenerateID();
  core->path = "/field";
  messenger->sendSignal("/field", "createBoxField",
                        FLEX_ARGS(FLEX_STRING(core->name) FLEX_STRING(
                            parent ? parent->getNodePath() : std::string(""))
                                      FLEX_VEC3(origin) FLEX_QUAT(rotation)
                                          FLEX_VEC3(size)));
}

void BoxField::setSize(Vec3 size) {
  sendSignal("setSize", FLEX_ARG(FLEX_VEC3(size)));
}

} // namespace StardustXRFusion
