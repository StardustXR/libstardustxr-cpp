#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "spatial.hpp"
#include "../fields/field.hpp"

namespace flexbuffers {
	class Reference;
}

namespace StardustXRFusion {

class Zone : public Spatial {
public:
	explicit Zone(Spatial *parent, Field &field, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity);
	~Zone();

	void isCaptured(Spatial &spatial, std::function<void(bool)> callback);
	void capture(Spatial &spatial);
	void release(Spatial &spatial);

	std::function<void(Spatial &)> onSpatialEnter = [](Spatial &){};
	std::function<void(std::string &)> onSpatialLeave = [](std::string &){};

private:
	std::map<std::string, Spatial> spatials;
	std::vector<uint8_t> updateZone(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
