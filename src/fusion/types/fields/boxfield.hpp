#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class BoxField : public Field {
public:
	BoxField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size);

	void setSize(SKMath::vec3 size);
};

} // namespace StardustXRFusion
