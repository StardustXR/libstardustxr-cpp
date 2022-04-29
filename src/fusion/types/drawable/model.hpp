#pragma once

#include <string>

#include "../spatial/spatial.hpp"

namespace StardustXRFusion {

class Model : public Spatial {
public:
	explicit Model(Spatial *parent, std::string relativePath, Vec3 origin = Vec3::Zero, Quat rotation = Quat::Identity, Vec3 scale = Vec3::One);

	void setMaterialProperty(uint32_t submesh, std::string propertyName, float value);
	void setMaterialProperty(uint32_t submesh, std::string propertyName, Color col);
	void setMaterialProperty(uint32_t submesh, std::string propertyName, std::string value);

	operator bool()const {
		return valid;
	}
protected:
	bool valid = false;
};

} // namespace StardustXRFusion
