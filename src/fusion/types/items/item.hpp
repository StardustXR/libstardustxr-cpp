#pragma once

#include "../spatial/spatial.hpp"
#include <functional>

namespace StardustXRFusion {

class Item : public Spatial {
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
	Item(bool destroyable);
};

}
