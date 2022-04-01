#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class SphereField : public Field {
public:
	SphereField(Spatial *parent, SKMath::vec3 origin, float radius);
};

} // namespace StardustXRFusion
