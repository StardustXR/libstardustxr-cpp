#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class CylinderField : public Field {
public:
	explicit CylinderField(Spatial *parent, Vec3 origin, Quat rotation, float length, float radius);
};

} // namespace StardustXRFusion
