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
	explicit Zone(Spatial *parent, Field &field, Vec3 origin = Vec3::Zero, Quat rotation = Quat::Identity);
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
