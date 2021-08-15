#pragma once

#include "datamap.hpp"
#include "../spatial.hpp"
#include "../fields/field.hpp"

namespace flexbuffers {
	class Reference;
}

namespace StardustXRFusion {

class HandInput;
class PointerInput;

class InputHandler : public Spatial {
public:
	explicit InputHandler(Spatial *space, Field &field, SKMath::vec3 origin, SKMath::quat orientation);

	std::function<bool(const PointerInput &, const Datamap &)> pointerHandlerMethod = [](const PointerInput &, const Datamap &) {
		return false;
	};
	std::function<bool(const HandInput &, const Datamap &)> handHandlerMethod = [](const HandInput &, const Datamap &) {
		return false;
	};

private:
	std::vector<uint8_t> inputEvent(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
