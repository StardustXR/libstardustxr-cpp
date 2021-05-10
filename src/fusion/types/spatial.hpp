#pragma once

#include "node.hpp"
#include "../sk_math.hpp"

namespace StardustXRFusion {

class Spatial : public Node {
public:
	explicit Spatial();
	~Spatial();

	static Spatial create(SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity, SKMath::vec3 scale = SKMath::vec3_one, bool translatable = true, bool rotatable = true, bool scalable = true);

	void move(SKMath::vec3 position);
	void rotate(SKMath::quat rotation);
	void rotateAround(SKMath::vec3 point, SKMath::quat rotation);
	void scale(float scaleFactor);

	void setOrigin(SKMath::vec3 origin);
	void setOrientation(SKMath::quat orientation);
	void setScale(SKMath::vec3 scale);
	void setPose(SKMath::pose_t pose);

	void setSpatialParent(Spatial *space);
};

} // namespace StardustXRFusion
