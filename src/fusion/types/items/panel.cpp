#include "panel.hpp"
#include "../../scenegraph.hpp"
#include "fusion_internal.hpp"
#include <cstddef>
#include <flatbuffers/flexbuffers.h>
#include <string>
#include <vector>

namespace StardustXRFusion {

std::function<void(bool, PanelItem &, uint32_t, uint32_t)> PanelItem::uiCallbackFunction = [](bool, PanelItem &, uint32_t, uint32_t) {};

PanelItem::PanelItem(Spatial *space, std::string nodePath, std::string nodeName) :
	Item(space, nodePath, nodeName) {
}
void PanelItem::registerUIHandler(std::function<void(bool, PanelItem &, uint32_t, uint32_t)> callback) {
	uiCallbackFunction = callback;
	scenegraph->addMethod("panelUI", &PanelItem::uiCallback);

	messenger->sendSignal(
		"/item",
		"registerPanelItemUI",
		FLEX_ARGS(
			FLEX_STRING(std::string(""))
			FLEX_STRING(std::string("panelUI"))
		)
	);
}

void PanelItem::applySurfaceMaterial(Model &model, uint32_t submeshIndex) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"applySurfaceMaterial",
		FLEX_ARGS(
			FLEX_STRING(model.getNodePath())
			fbb.UInt(submeshIndex);
		)
	);
}

void PanelItem::getData(std::function<void (uint32_t, uint32_t)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"getData",
		FLEX_ARG(FLEX_NULL),
		[callback](flexbuffers::Reference data) {
			flexbuffers::Vector dataVec = data.AsVector();
			callback(
				dataVec[0].AsUInt32(),
				dataVec[1].AsUInt32()
			);
		}
	);
}

void PanelItem::setPointerActive(bool active) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setPointerActive",
		FLEX_ARG(FLEX_BOOL(active))
	);
}
void PanelItem::setPointerPosition(SKMath::vec2 pos) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setPointerPosition",
		FLEX_ARGS(
			FLEX_DOUBLE(pos.x)
			FLEX_DOUBLE(pos.y)
		)
	);
}
void PanelItem::setPointerButtonPressed(uint32_t button, bool pressed) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setPointerButtonPressed",
		FLEX_ARGS(
			FLEX_UINT(button)
			FLEX_BOOL(pressed)
		)
	);
}
void PanelItem::scrollPointerAxis(uint32_t source, double x, double y, int32_t dx, int32_t dy) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"scrollPointerAxis",
		FLEX_ARGS(
			FLEX_UINT(source)
			FLEX_DOUBLE(x)
			FLEX_DOUBLE(y)
			FLEX_INT(dx)
			FLEX_INT(dy)
		)
	);
}

void PanelItem::resize(uint32_t width, uint32_t height) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"resize",
		FLEX_ARGS(
			FLEX_UINT(width)
			FLEX_UINT(height)
		)
	);
}
void PanelItem::close() {
	messenger->sendSignal(
		getNodePath().c_str(),
		"close",
		FLEX_ARG(FLEX_NULL)
	);
}

std::vector<uint8_t> PanelItem::uiCallback(flexbuffers::Reference data, bool) {
	flexbuffers::Vector flexVec = data.AsVector();
	bool created = flexVec[0].AsBool();
	std::string nodeName = flexVec[1].AsString().str();
	flexbuffers::Vector dataVec = flexVec[2].AsVector();

	PanelItem item(nullptr, "/item/panel", nodeName);
	uiCallbackFunction(created, item, dataVec[0].AsUInt32(), dataVec[1].AsUInt32());
	return std::vector<uint8_t>();
}

}
