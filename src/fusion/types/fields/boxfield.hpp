#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class BoxField : public Field {
public:
	explicit BoxField(Spatial *parent, Vec3 origin, Quat rotation, Vec3 size);

	void setSize(Vec3 size);
};

} // namespace StardustXRFusion
