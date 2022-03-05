#pragma once

#include "../spatial/spatial.hpp"
#include <functional>

namespace StardustXRFusion {

class Item : public StardustXRFusion::Spatial {
public:
	enum UIEvent {
		Create  = 0,
		Capture = 1,
		Release = 2,
		Destroy = 3
	};
	void triggerAccept();
	void release();

protected:
	Item(Spatial *space, SKMath::vec3 origin, SKMath::quat orientation);
	Item(Spatial *space, std::string nodePath, std::string nodeName);
};

}
