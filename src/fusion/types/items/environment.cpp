#include "environment.hpp"
#include "../../scenegraph.hpp"
#include "fusion_internal.hpp"
#include <cstddef>
#include <flatbuffers/flexbuffers.h>
#include <string>
#include <vector>

namespace StardustXRFusion {

std::function<void(bool, EnvironmentItem &)> EnvironmentItem::uiCallbackFunction = [](bool, EnvironmentItem &) {};

EnvironmentItem::EnvironmentItem(Spatial *space, const std::string path, SKMath::vec3 origin, SKMath::quat orientation) : 
	Item(space, origin, orientation) {

	nodeName = GenerateID();
	nodePath = "/item/environment";

	messenger->sendSignal(
		"/item",
		"createEnvironmentItem",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(space ? space->getNodePath() : std::string(""))
			FLEX_STRING(path)
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
		)
	);
}

EnvironmentItem::EnvironmentItem(Spatial *space, const std::string path, std::string nodePath, std::string nodeName) : 
	Item(space, nodePath, nodeName), path(path) {
}
void EnvironmentItem::registerUIHandler(std::function<void(bool, EnvironmentItem &)> callback) {
	uiCallbackFunction = callback;
	scenegraph->methods["environmentUI"] = &EnvironmentItem::uiCallback;

	messenger->sendSignal(
		"/item",
		"registerEnvironmentItemUI",
		FLEX_ARGS(
			FLEX_STRING(std::string(""))
			FLEX_STRING(std::string("environmentUI"))
		)
	);
}

std::vector<uint8_t> EnvironmentItem::uiCallback(flexbuffers::Reference data, bool) {
	flexbuffers::Vector flexVec = data.AsVector();
	bool created = flexVec[0].AsBool();
	std::string nodeName = flexVec[1].AsString().str();
	std::string path = flexVec[2].AsVector()[0].AsString().str();

	EnvironmentItem item(nullptr, path, "/item/environment", nodeName);
	uiCallbackFunction(created, item);
	return std::vector<uint8_t>();
}

}
