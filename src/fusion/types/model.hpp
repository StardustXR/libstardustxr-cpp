#pragma once

#include <string>

#include "spatial.hpp"

namespace StardustXRFusion {

class Model : public Spatial {
public:
	explicit Model(std::string relativePath, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale);
	~Model();
};

} // namespace StardustXRFusion

