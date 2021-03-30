#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class SphereField : public Field {
public:
	explicit SphereField(SKMath::vec3 origin, float radius);
	~SphereField();
};

} // namespace StardustXRFusion
