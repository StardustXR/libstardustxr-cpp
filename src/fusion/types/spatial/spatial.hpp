#pragma once

#include <functional>

#include "../node.hpp"
#include "../../values.hpp"

namespace StardustXRFusion {

class Spatial : public Node {
public:
	explicit Spatial();
	explicit Spatial(Spatial *parent, Vec3 origin = Vec3::Zero, Quat rotation = Quat::Identity, Vec3 scale = Vec3::One, bool translatable = true, bool rotatable = true, bool scalable = true, bool zoneable = false);

	void createLaunchAnchor(std::function<void(uint32_t)> callback);

	void getTransform(Spatial *space, std::function<void(Vec3, Quat, Vec3)> callback);

	void setOrigin(Vec3 origin, Spatial &space);
	void setOrigin(Vec3 origin);

	void setOrientation(Quat rotation, Spatial &space);
	void setOrientation(Quat rotation);

	void setPose(Pose pose, Spatial &space);
	void setPose(Pose pose);

	void setScale(Vec3 scale);

	void setSpatialParent(Spatial *space);
	void setSpatialParentInPlace(Spatial *space);

	void setZoneable(bool zoneable);

protected:
	Spatial(bool destroyable);
};

} // namespace StardustXRFusion
