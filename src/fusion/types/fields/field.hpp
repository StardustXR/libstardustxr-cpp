#pragma once

#include "../spatialnode.hpp"
#include "../../sk_math.hpp"

namespace StardustXRFusion {

class Field : public SpatialNode {
public:
	explicit Field();
	~Field();

	void distance		(SpatialNode *space, SKMath::vec3 point, std::function<void (float)> callback);
	void normal			(SpatialNode *space, SKMath::vec3 point, std::function<void (SKMath::vec3)> callback);
	void closestPoint	(SpatialNode *space, SKMath::vec3 point, std::function<void (SKMath::vec3)> callback);
};

} // namespace StardustXRFusion
