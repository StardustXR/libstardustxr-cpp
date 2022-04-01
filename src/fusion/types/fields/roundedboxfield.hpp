#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class RoundedBoxField : public Field {
public:
	RoundedBoxField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size);
};

} // namespace StardustXRFusion
