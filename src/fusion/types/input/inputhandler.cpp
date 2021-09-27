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

namespace StardustXRFusion {

InputHandler::InputHandler(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation) : Spatial(parent, origin, orientation, vec3_one) {
	nodeName = GenerateID();
	nodePath = "/input/handler";

	scenegraph->methods[nodeName] = std::bind(&InputHandler::inputEvent, this, std::placeholders::_1, std::placeholders::_2);
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

	scenegraph->methods[nodeName] = std::bind(&InputHandler::inputEvent, this, std::placeholders::_1, std::placeholders::_2);
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

void InputHandler::getInputHandlers(Spatial *space, bool excludeSelf, std::function<void(std::vector<InputActions> &)> callback) {
	std::string spacePath = (space) ? space->getNodePath() : "";
	messenger->executeRemoteMethod(
		"/input",
		"getInputHandlers",
		FLEX_ARGS(
			FLEX_STRING(spacePath)
			FLEX_BOOL(excludeSelf)
		),
		[callback, space](flexbuffers::Reference data) {
			std::vector<InputActions> basics;
			flexbuffers::Vector basicsFlexVec = data.AsVector();
			for(uint i=0; i<data.AsVector().size(); ++i) {
				flexbuffers::Vector basicsFlex = basicsFlexVec[i].AsVector();
				std::string basicsUUID = basicsFlex[0].AsString().str();
				flexbuffers::TypedVector basicsFlexPoint = basicsFlex[1].AsTypedVector();
				SKMath::vec3 basicsPosition = {
					basicsFlexPoint[0].AsFloat(),
					basicsFlexPoint[1].AsFloat(),
					basicsFlexPoint[2].AsFloat()
				};
				basics.emplace_back(basicsUUID, basicsPosition, space);
			}
			
			callback(basics);
		}
	);
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

void InputHandler::updateActions() {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setActions",
		FLEX_ARG(
			fbb.TypedVector([&] {
				for(auto actionSet : actions) {
					fbb.String(actionSet.first);
				}
			});
		)
	);
}

void InputHandler::runAction(std::string action) {
	if(actions.find(action) == actions.end())
		return;
	
	messenger->sendSignal(
		getNodePath().c_str(),
		"runAction",
		FLEX_ARG(
			FLEX_STRING(action);
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
		case StardustXR::InputDataRaw_Action: {
			const StardustXR::Action *action = inputData->input_as_Action();
			std::string actionName = action->name()->str();
			if(actions.find(actionName) != actions.end())
				actions[actionName]();
		} break;
		default: break;
	}
	return FLEX_SINGLE(FLEX_BOOL(capture));
}

} // namespace StardustXRFusion
