#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class BoxField : public Field {
public:
	explicit BoxField(SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size);
	~BoxField();
};

} // namespace StardustXRFusion
