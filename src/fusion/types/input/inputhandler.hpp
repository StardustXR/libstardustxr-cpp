#pragma once

#include "../spatial.hpp"
#include "../fields/field.hpp"

#include "flatbuffers/Input_generated.h"

namespace StardustXRFusion {

typedef std::function<bool(const StardustXR::InputData *)> InputHandlerMethod;

class InputHandler : public Spatial {
public:
	explicit InputHandler(Spatial *space, Field &field, SKMath::vec3 origin, SKMath::quat orientation, InputHandlerMethod handlerMethod);

private:
	InputHandlerMethod handlerMethod;
	std::vector<uint8_t> inputEvent(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
