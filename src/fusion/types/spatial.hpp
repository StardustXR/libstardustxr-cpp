#pragma once

#include "node.hpp"
#include "../sk_math.hpp"

namespace StardustXRFusion {

class Spatial : public Node {
public:
	explicit Spatial();
	~Spatial();

	void setOrigin(SKMath::vec3 origin);
	void setOrientation(SKMath::quat orientation);
	void setScale(SKMath::vec3 scale);
	void setPose(SKMath::pose_t pose);
};

} // namespace StardustXRFusion
