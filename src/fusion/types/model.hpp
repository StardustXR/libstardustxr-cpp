#pragma once

#include <string>

#include "spatial.hpp"

namespace StardustXRFusion {

class Model : public Spatial {
public:
	explicit Model(std::string relativePath, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity, SKMath::vec3 scale = SKMath::vec3_one);
	~Model();
};

} // namespace StardustXRFusion

