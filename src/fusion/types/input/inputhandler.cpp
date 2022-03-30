#include "../../fusion_internal.hpp"
#include "../../flex.hpp"
#include "../../scenegraph.hpp"
#include "sk_math.hpp"
#include "types/handinput.hpp"
#include "types/pointerinput.hpp"

#include "../../../common/flatbuffers/Input.hpp"

#include "inputhandler.hpp"
#include <flatbuffers/flexbuffers.h>
#include <map>
#include <string>
#include <variant>

using namespace SKMath;

namespace StardustXRFusion {

InputHandler::InputHandler(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation) : Spatial(true) {
	nodePath = "/input/handler";
	nodeName = GenerateID();

	scenegraph->addMethod(nodeName, std::bind(&InputHandler::inputEvent, this, std::placeholders::_1, std::placeholders::_2));
	messenger->sendSignal(
		"/input",
		"registerInputHandler",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(field.getNodePath())
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
}
InputHandler::InputHandler(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation) : Spatial(parent, origin, orientation, vec3_one) {
	nodeName = GenerateID();
	nodePath = "/input/handler";

	messenger->sendSignal(
		"/input",
		"registerInputHandler",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(std::string(""))
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
}
InputHandler::~InputHandler() {
}

void InputHandler::setField(Field *field) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setField",
		FLEX_ARG(
			FLEX_STRING(field == nullptr ? std::string("") : field->getNodePath())
		)
	);
}

std::vector<uint8_t> InputHandler::inputEvent(flexbuffers::Reference data, bool) {
	const StardustXR::InputData *inputData = StardustXR::GetInputData(data.AsBlob().data());
	const Datamap datamap(inputData->datamap()->data(), inputData->datamap()->Length());

	bool capture = false;
	switch (inputData->input_type()) {
		case StardustXR::InputDataRaw_Hand: {
			HandInput hand(inputData);
			capture = handHandlerMethod(inputData->uuid()->str(), hand, datamap);
		} break;
		case StardustXR::InputDataRaw_Pointer: {
			PointerInput pointer(inputData);
			capture = pointerHandlerMethod(inputData->uuid()->str(), pointer, datamap);
		} break;
		default: break;
	}
	return FLEX_SINGLE(FLEX_BOOL(capture));
}

} // namespace StardustXRFusion
