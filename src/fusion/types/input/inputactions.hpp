#pragma once

#include "datamap.hpp"
#include "../spatial.hpp"
#include "../fields/field.hpp"
#include "sk_math.hpp"

namespace flexbuffers {
	class Reference;
}

namespace StardustXRFusion {

class InputActions : public Node {
public:
	explicit InputActions(std::string uuid, SKMath::vec3 position, Spatial *relativeSpace);
	void getActions(std::function<void(std::vector<std::string> &)> callback);
	void runAction(std::string action);
	
	std::string uuid;
	SKMath::vec3 position;
	Spatial *relativeSpace;

private:
	std::vector<uint8_t> inputEvent(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
