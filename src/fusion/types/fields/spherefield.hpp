#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class SphereField : public Field {
public:
	explicit SphereField(Spatial *parent, Vec3 origin, float radius);
};

} // namespace StardustXRFusion
