#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class RoundedBoxField : public Field {
public:
	explicit RoundedBoxField(Spatial *parent, Vec3 origin, Quat rotation, Vec3 size);
};

} // namespace StardustXRFusion
