#pragma once

#include <functional>

#include "../spatial/spatial.hpp"
#include "../../values.hpp"

namespace StardustXRFusion {

class Field : public Spatial {
public:
	void distance		(Spatial *space, Vec3 point, std::function<void (float)> callback);
	void normal			(Spatial *space, Vec3 point, std::function<void (Vec3)> callback);
	void closestPoint	(Spatial *space, Vec3 point, std::function<void (Vec3)> callback);
protected:
	explicit Field();
};

} // namespace StardustXRFusion
