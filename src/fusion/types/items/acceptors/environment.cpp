#include "environment.hpp"
#include "fusion_internal.hpp"

namespace StardustXRFusion {

EnvironmentItemAcceptor::EnvironmentItemAcceptor(Spatial *parent, Field &field,
                                                 Vec3 origin, Quat rotation)
    : ItemAcceptor(parent, field, origin, rotation, "environment") {}

std::vector<uint8_t>
EnvironmentItemAcceptor::acceptorCallback(flexbuffers::Reference data, bool) {
  flexbuffers::Vector flexVec = data.AsVector();
  bool captured = flexVec[0].AsBool();
  std::string nodeName = flexVec[1].AsString().str();
  flexbuffers::Vector dataVec = flexVec[2].AsVector();

  EnvironmentItem item("/item/panel", nodeName);
  if (captured)
    itemCapturedMethod(item,
                       EnvironmentItem::Data{dataVec[0].AsString().str()});
  else
    itemReleasedMethod(item);
  return std::vector<uint8_t>();
}

} // namespace StardustXRFusion
