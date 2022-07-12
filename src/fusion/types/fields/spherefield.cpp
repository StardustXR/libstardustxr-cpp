#include "../../flex.hpp"
#include "../../fusion_internal.hpp"

#include "spherefield.hpp"
#include "values.hpp"

namespace StardustXRFusion {

SphereField::SphereField(Spatial *parent, Vec3 origin, float radius) {
  core->name = GenerateID();
  core->path = "/field";
  messenger->sendSignal("/field", "createSphereField",
                        FLEX_ARGS(FLEX_STRING(core->name) FLEX_STRING(
                            parent ? parent->getNodePath() : std::string(""))
                                      FLEX_VEC3(origin) FLEX_FLOAT(radius)));
}

} // namespace StardustXRFusion
