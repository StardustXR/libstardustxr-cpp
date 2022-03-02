#include "panel.hpp"
#include "fusion_internal.hpp"
#include "../../../scenegraph.hpp"
#include <cstddef>
#include <flatbuffers/flexbuffers.h>
#include <string>
#include <vector>

namespace StardustXRFusion {

std::string PanelItem::createAcceptorMethodString = "createPanelItemAcceptor";

std::function<void(PanelItem &, PanelItem::Data)> PanelItem::uiCreateFunction  = [](PanelItem &, PanelItem::Data) {};
std::function<void(PanelItem &)>                  PanelItem::uiDestroyFunction = [](PanelItem &) {};

PanelItem::PanelItem(Spatial *space, std::string nodePath, std::string nodeName) :
	Item(space, nodePath, nodeName) {
}

void PanelItem::registerUIHandlers(std::function<void (PanelItem &, Data)> create, std::function<void (PanelItem &)> destroy) {
	uiCreateFunction = create;
	uiDestroyFunction = destroy;
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
			FLEX_UINT(submeshIndex);
		)
	);
}

void PanelItem::getData(std::function<void (Data)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"getData",
		FLEX_ARG(FLEX_NULL),
		[callback](flexbuffers::Reference data) {
			flexbuffers::Vector dataVec = data.AsVector();
			callback(Data {
				dataVec[0].AsUInt32(),
				dataVec[1].AsUInt32()
			});
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

void PanelItem::touchDown(uint32_t id, double x, double y) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"touchDown",
		FLEX_ARGS(
			FLEX_UINT(id)
			FLEX_DOUBLE(x)
			FLEX_DOUBLE(y)
		)
	);
}
void PanelItem::touchMove(uint32_t id, double x, double y) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"touchMove",
		FLEX_ARGS(
			FLEX_UINT(id)
			FLEX_DOUBLE(x)
			FLEX_DOUBLE(y)
		)
	);
}
void PanelItem::touchUp(uint32_t id) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"touchUp",
		FLEX_ARG(
			FLEX_UINT(id)
		)
	);
}

void PanelItem::setKeyboardActive(bool active) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setKeyboardActive",
		FLEX_ARG(
			FLEX_BOOL(active)
		)
	);
}
void PanelItem::setKeymap(std::string data) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setKeymap",
		FLEX_ARG(
			FLEX_STRING(data)
		)
	);
}
void PanelItem::setKeyState(uint32_t key, bool state) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setKeyState",
		FLEX_ARGS(
			FLEX_UINT(key)
			FLEX_UINT(state)
		)
	);
}
void PanelItem::setKeyModStates(xkb_mod_mask_t depressed, xkb_mod_mask_t latched, xkb_mod_mask_t locked, xkb_mod_mask_t group) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setKeyModStates",
		FLEX_ARGS(
			FLEX_UINT(depressed)
			FLEX_UINT(latched)
			FLEX_UINT(locked)
			FLEX_UINT(group)
		)
	);
}
void PanelItem::setKeyRepeat(int32_t rate, int32_t delayMS) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setKeyRepeat",
		FLEX_ARGS(
			FLEX_INT(rate)
			FLEX_INT(delayMS)
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
	if(created)
		uiCreateFunction(item, Data {dataVec[0].AsUInt32(), dataVec[1].AsUInt32()});
	else
		uiDestroyFunction(item);
	return std::vector<uint8_t>();
}

}
