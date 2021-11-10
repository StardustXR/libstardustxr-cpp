#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class CylinderField : public Field {
public:
	explicit CylinderField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, float length, float radius);
};

} // namespace StardustXRFusion
