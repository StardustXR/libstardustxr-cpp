#include "../../fusion_internal.hpp"
#include "../../flex.hpp"
#include "../../scenegraph.hpp"

#include "inputhandler.hpp"

namespace StardustXRFusion {

InputHandler::InputHandler(Spatial *space, Field *field, SKMath::vec3 origin, SKMath::quat orientation, InputHandlerMethod handlerMethod) {
	nodeName = GenerateID();
	nodePath = "/input/handler";

	scenegraph->methods[nodeName] = std::bind(&InputHandler::inputEvent, this, std::placeholders::_1, std::placeholders::_2);
	messenger->sendSignal(
		"/input",
		"registerInputHandler",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(field->getNodePath())
//			FLEX_STRING(space ? space->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
	this->handlerMethod = handlerMethod;
}

std::vector<uint8_t> InputHandler::inputEvent(flexbuffers::Reference data, bool) {
	const StardustXR::InputData *inputData = StardustXR::GetInputData(data.AsBlob().data());
	bool capture = handlerMethod(inputData);

	return FLEX_SINGLE(FLEX_BOOL(capture));
}

} // namespace StardustXRFusion
