#pragma once

#include <functional>

#include "../spatial.hpp"
#include "../../sk_math.hpp"

namespace StardustXRFusion {

class Field : public Spatial {
public:
	explicit Field(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation);

	void distance		(Spatial *space, SKMath::vec3 point, std::function<void (float)> callback);
	void normal			(Spatial *space, SKMath::vec3 point, std::function<void (SKMath::vec3)> callback);
	void closestPoint	(Spatial *space, SKMath::vec3 point, std::function<void (SKMath::vec3)> callback);

	static Field &Empty();
private:
	static Field *empty;
};

} // namespace StardustXRFusion
