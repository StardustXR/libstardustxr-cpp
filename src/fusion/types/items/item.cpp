#include "item.hpp"
#include "types/spatial.hpp"

namespace StardustXRFusion {

Item::Item(Spatial *space, std::string nodePath, std::string nodeName) : Spatial(space, nodePath, nodeName) {
	destroyable = false;
}
Item::Item(Spatial *space, SKMath::vec3 origin, SKMath::quat orientation) : Spatial(space, origin, orientation) {
	destroyable = false;
}

}
