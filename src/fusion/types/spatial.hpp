#pragma once

#include <functional>

#include "node.hpp"
#include "../sk_math.hpp"

namespace StardustXRFusion {

class Spatial : public Node {
public:
	explicit Spatial(Spatial *parent, std::string nodePath, std::string nodeName);
	explicit Spatial(Spatial *parent, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity, SKMath::vec3 scale = SKMath::vec3_one);
	static Spatial create(Spatial *parent, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity, SKMath::vec3 scale = SKMath::vec3_one, bool translatable = true, bool rotatable = true, bool scalable = true, bool zoneable = false);

	void move(SKMath::vec3 position);
	void rotate(SKMath::quat rotation);
	void scale(float scaleFactor);

	void getTransform(std::function<void(SKMath::vec3, SKMath::quat, SKMath::vec3)> callback);

	void setOrigin(SKMath::vec3 origin);
	void setOrientation(SKMath::quat orientation);
	void setScale(SKMath::vec3 scale);
	void setPose(SKMath::pose_t pose);

	SKMath::vec3 getOrigin();
	SKMath::quat getOrientation();
	SKMath::vec3 getScale();
	SKMath::pose_t getPose();

	Spatial *getSpatialParent();
	void setSpatialParent(Spatial *space);
	void setSpatialParentInPlace(Spatial *space);

	void setZoneable(bool zoneable);

protected:
	SKMath::vec3 origin;
	SKMath::quat orientation;
	SKMath::vec3 localScale;
	Spatial *parent = nullptr;
};

} // namespace StardustXRFusion
