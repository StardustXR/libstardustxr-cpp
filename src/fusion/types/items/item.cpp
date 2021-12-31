#include "item.hpp"
#include "types/spatial.hpp"
#include "fusion_internal.hpp"

namespace StardustXRFusion {

Item::Item(Spatial *space, std::string nodePath, std::string nodeName) : Spatial(space, nodePath, nodeName) {
	destroyable = false;
}
Item::Item(Spatial *space, SKMath::vec3 origin, SKMath::quat orientation) : Spatial(space, origin, orientation) {
	destroyable = false;
}

void Item::triggerAccept() {
	messenger->sendSignal(
		getNodePath().c_str(),
		"triggerAccept",
		FLEX_ARG(FLEX_NULL)
	);
}
void Item::release() {
	messenger->sendSignal(
		getNodePath().c_str(),
		"release",
		FLEX_ARG(FLEX_NULL)
	);
}

}
