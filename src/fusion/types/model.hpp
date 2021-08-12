#pragma once

#include <string>

#include "spatial.hpp"

namespace StardustXRFusion {

class Model : public Spatial {
public:
	explicit Model(std::string relativePath, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity, SKMath::vec3 scale = SKMath::vec3_one);
	~Model();

	void setMaterialProperty(uint32_t submesh, std::string propertyName, float value);
	void setMaterialProperty(uint32_t submesh, std::string propertyName, SKMath::color col);
	void setMaterialProperty(uint32_t submesh, std::string propertyName, std::string value);

	operator bool()const {
		return valid;
	}
protected:
	bool valid = false;
};

} // namespace StardustXRFusion
