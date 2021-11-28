#pragma once

#include "../spatial.hpp"
#include <functional>

namespace StardustXRFusion {

class Item : public StardustXRFusion::Spatial {
public:
	Item(Spatial *space, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity);

protected:
	Item(Spatial *space, std::string nodePath, std::string nodeName);
};

}
