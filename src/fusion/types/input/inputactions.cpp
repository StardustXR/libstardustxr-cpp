#include "inputactions.hpp"

#include "../../fusion_internal.hpp"
#include "../../flex.hpp"
// #include "../../scenegraph.hpp"

namespace StardustXRFusion {

InputActions::InputActions(std::string uuid, SKMath::vec3 position, Spatial *relativeSpace) {
	this->uuid = uuid;
	this->position = position;
	this->relativeSpace = relativeSpace;

	this->nodeName = uuid;
	this->nodePath = "/input/global_handlers/";
}

void InputActions::getActions(std::function<void(std::vector<std::string> &)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"getActions",
		FLEX_ARG(FLEX_NULL),
		[callback](flexbuffers::Reference data) {
			std::vector<std::string> actions;
			flexbuffers::TypedVector actionsFlexVec = data.AsTypedVector();
			for(uint i=0; i<actionsFlexVec.size(); ++i) {
				actions.push_back(actionsFlexVec[i].AsString().str());
			}
			callback(actions);
		}
	);
}
void InputActions::runAction(std::string action) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"runAction",
		FLEX_ARG(
			FLEX_STRING(action)
		)
	);
}

}