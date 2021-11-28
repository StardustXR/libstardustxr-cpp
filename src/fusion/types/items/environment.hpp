#pragma once

#include "item.hpp"
#include <functional>
#include <string>
#include <vector>

namespace flexbuffers {
	class Reference;
}

namespace StardustXRFusion {

class EnvironmentItem : public Item {
public:
	EnvironmentItem(Spatial *space, const std::string path, SKMath::vec3 origin, SKMath::quat orientation);

	static void registerUIHandler(std::function<void(bool, EnvironmentItem &)> callback);

	const std::string path;

private:
	EnvironmentItem(Spatial *space, const std::string path, std::string nodePath, std::string nodeName);
	static std::vector<uint8_t> uiCallback(flexbuffers::Reference data, bool);
	static std::function<void(bool, EnvironmentItem &)> uiCallbackFunction;
};

}
