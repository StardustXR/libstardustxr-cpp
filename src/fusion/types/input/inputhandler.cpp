#include "../../fusion_internal.hpp"
#include "../../flex.hpp"
#include "../../scenegraph.hpp"
#include "types/handinput.hpp"
#include "types/pointerinput.hpp"

#include "../../../common/flatbuffers/Input.hpp"

#include "inputhandler.hpp"
#include <flatbuffers/flexbuffers.h>
#include <map>
#include <string>
#include <variant>

namespace StardustXRFusion {

InputHandler::InputHandler(Spatial *space, Field &field, SKMath::vec3 origin, SKMath::quat orientation) {
	nodeName = GenerateID();
	nodePath = "/input/handler";

	scenegraph->methods[nodeName] = std::bind(&InputHandler::inputEvent, this, std::placeholders::_1, std::placeholders::_2);
	messenger->sendSignal(
		"/input",
		"registerInputHandler",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(field.getNodePath())
//			FLEX_STRING(space ? space->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
}

std::vector<uint8_t> InputHandler::inputEvent(flexbuffers::Reference data, bool) {
	const StardustXR::InputData *inputData = StardustXR::GetInputData(data.AsBlob().data());
	const flexbuffers::Map flexDatamap = inputData->datamap_flexbuffer_root().AsMap();
	Datamap datamap(flexDatamap);

	bool capture = false;
	switch (inputData->input_type()) {
		case StardustXR::InputDataRaw_Hand: {
			HandInput hand(inputData);
			capture = handHandlerMethod(hand, datamap);
		} break;
		case StardustXR::InputDataRaw_Pointer: {
			PointerInput pointer(inputData);
			capture = pointerHandlerMethod(pointer, datamap);
		} break;
		default: break;
	}
	return FLEX_SINGLE(FLEX_BOOL(capture));
}

} // namespace StardustXRFusion
