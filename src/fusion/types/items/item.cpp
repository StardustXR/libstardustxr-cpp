#include "item.hpp"
#include "../spatial/spatial.hpp"
#include "fusion_internal.hpp"

namespace StardustXRFusion {

Item::Item() : Spatial() {}

void Item::triggerAccept() {
  messenger->sendSignal(getNodePath().c_str(), "triggerAccept",
                        FLEX_ARG(FLEX_NULL));
}
void Item::release() {
  messenger->sendSignal(getNodePath().c_str(), "release", FLEX_ARG(FLEX_NULL));
}

} // namespace StardustXRFusion
