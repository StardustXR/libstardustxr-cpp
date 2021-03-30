#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class RoundedBoxField : public Field {
public:
	explicit RoundedBoxField(SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size);
	~RoundedBoxField();
};

} // namespace StardustXRFusion
