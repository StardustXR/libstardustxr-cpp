#pragma once

#include "../spatial/spatial.hpp"
#include <functional>

namespace StardustXRFusion {

class Item : public StardustXRFusion::Spatial {
public:
	void triggerAccept();
	void release();

protected:
	Item(Spatial *space, SKMath::vec3 origin, SKMath::quat orientation);
	Item(Spatial *space, std::string nodePath, std::string nodeName);
};

}
