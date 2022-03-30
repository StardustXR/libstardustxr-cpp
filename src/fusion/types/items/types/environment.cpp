#include "environment.hpp"
#include "fusion_internal.hpp"
#include "../../../scenegraph.hpp"
#include <cstddef>
#include <flatbuffers/flexbuffers.h>
#include <string>
#include <vector>

namespace StardustXRFusion {

std::string EnvironmentItem::createAcceptorMethodString = "createEnvironmentItemAcceptor";

std::function<void(EnvironmentItem &, EnvironmentItem::Data)> EnvironmentItem::uiCreateFunction  = [](EnvironmentItem &, EnvironmentItem::Data) {};
std::function<void(EnvironmentItem &)>                        EnvironmentItem::uiDestroyFunction = [](EnvironmentItem &) {};

EnvironmentItem::EnvironmentItem(Spatial *space, const std::string path, SKMath::vec3 origin, SKMath::quat orientation) : 
	Item(true) {

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

EnvironmentItem::EnvironmentItem(std::string nodePath, std::string nodeName) :
	Item(false) {
}

void EnvironmentItem::registerUIHandlers(std::function<void(EnvironmentItem &, Data)> create, std::function<void(EnvironmentItem &)> destroy) {
	uiCreateFunction = create;
	uiDestroyFunction = destroy;
	scenegraph->addMethod("panelUI", &EnvironmentItem::uiCallback);

	messenger->sendSignal(
		"/item",
		"registerEnvironmentItemUI",
		FLEX_ARGS(
			FLEX_STRING(std::string(""))
			FLEX_STRING(std::string("environmentUI"))
		)
	);
}

EnvironmentItem::Data EnvironmentItem::parseData(flexbuffers::Reference data) {

}

std::vector<uint8_t> EnvironmentItem::uiCallback(flexbuffers::Reference data, bool) {
	flexbuffers::Vector flexVec = data.AsVector();
	bool created = flexVec[0].AsBool();
	std::string nodeName = flexVec[1].AsString().str();
	std::string path = flexVec[2].AsVector()[0].AsString().str();

	EnvironmentItem item("/item/environment", nodeName);
	if(created)
		uiCreateFunction(item, Data {path});
	else
		uiDestroyFunction(item);
	return std::vector<uint8_t>();
}

}
