#pragma once

#include <functional>

#include "../spatial/spatial.hpp"
#include "../../sk_math.hpp"

namespace StardustXRFusion {

class Field : public Spatial {
public:
	void distance		(Spatial *space, SKMath::vec3 point, std::function<void (float)> callback);
	void normal			(Spatial *space, SKMath::vec3 point, std::function<void (SKMath::vec3)> callback);
	void closestPoint	(Spatial *space, SKMath::vec3 point, std::function<void (SKMath::vec3)> callback);
protected:
	explicit Field();
};

} // namespace StardustXRFusion
