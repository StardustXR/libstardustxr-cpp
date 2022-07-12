#include "panel.hpp"
#include "../../../scenegraph.hpp"
#include "fusion_internal.hpp"
#include <cstddef>
#include <flatbuffers/flexbuffers.h>
#include <string>
#include <vector>

namespace StardustXRFusion {

std::string PanelItem::createAcceptorMethodString = "createPanelItemAcceptor";

std::function<void(PanelItem &, PanelItem::Data)> PanelItem::uiCreateFunction =
    [](PanelItem &, PanelItem::Data) {};
std::function<void(PanelItem &)> PanelItem::uiCaptureFunction =
    [](PanelItem &) {};
std::function<void(PanelItem &, PanelItem::Data)> PanelItem::uiReleaseFunction =
    [](PanelItem &, PanelItem::Data) {};
std::function<void(PanelItem &)> PanelItem::uiDestroyFunction =
    [](PanelItem &) {};
std::shared_ptr<NodeCore> PanelItem::panelUICore(new NodeCore("/item", "panel",
                                                              true));

PanelItem::PanelItem(std::string nodePath, std::string nodeName) : Item() {
  this->core->path = nodePath;
  this->core->name = nodeName;
}

void PanelItem::registerUIHandlers(
    std::function<void(PanelItem &, Data)> create,
    std::function<void(PanelItem &)> capture,
    std::function<void(PanelItem &, Data)> release,
    std::function<void(PanelItem &)> destroy) {
  uiCreateFunction = create;
  uiCaptureFunction = capture;
  uiReleaseFunction = release;
  uiDestroyFunction = destroy;
  panelUICore->methods["panelUI"] = std::bind(
      &PanelItem::uiCallback, std::placeholders::_1, std::placeholders::_2);
  scenegraph->addNode(panelUICore);

  messenger->sendSignal("/item", "registerPanelItemUI", FLEX_ARGS(FLEX_NULL));
}

void PanelItem::applySurfaceMaterial(Model &model, uint32_t submeshIndex) {
  messenger->sendSignal(
      getNodePath().c_str(), "applySurfaceMaterial",
      FLEX_ARGS(FLEX_STRING(model.getNodePath()) FLEX_UINT(submeshIndex);));
}

void PanelItem::getData(std::function<void(Data)> callback) {
  executeMethod("getData", FLEX_ARG(FLEX_NULL),
                [callback](flexbuffers::Reference data) {
                  flexbuffers::Vector dataVec = data.AsVector();
                  callback(Data{dataVec[0].AsUInt32(), dataVec[1].AsUInt32()});
                });
}

void PanelItem::setPointerActive(bool active) {
  sendSignal("setPointerActive", FLEX_ARG(FLEX_BOOL(active)));
}
void PanelItem::setPointerPosition(Vec2 pos) {
  sendSignal("setPointerPosition",
             FLEX_ARGS(FLEX_DOUBLE(pos.x) FLEX_DOUBLE(pos.y)));
}
void PanelItem::setPointerButtonPressed(uint32_t button, bool pressed) {
  sendSignal("setPointerButtonPressed",
             FLEX_ARGS(FLEX_UINT(button) FLEX_BOOL(pressed)));
}
void PanelItem::scrollPointerAxis(uint32_t source, double x, double y,
                                  int32_t dx, int32_t dy) {
  sendSignal("scrollPointerAxis",
             FLEX_ARGS(FLEX_UINT(source) FLEX_DOUBLE(x) FLEX_DOUBLE(y)
                           FLEX_INT(dx) FLEX_INT(dy)));
}

void PanelItem::touchDown(uint32_t id, double x, double y) {
  sendSignal("touchDown",
             FLEX_ARGS(FLEX_UINT(id) FLEX_DOUBLE(x) FLEX_DOUBLE(y)));
}
void PanelItem::touchMove(uint32_t id, double x, double y) {
  sendSignal("touchMove",
             FLEX_ARGS(FLEX_UINT(id) FLEX_DOUBLE(x) FLEX_DOUBLE(y)));
}
void PanelItem::touchUp(uint32_t id) {
  sendSignal("touchUp", FLEX_ARG(FLEX_UINT(id)));
}

void PanelItem::setKeyboardActive(bool active) {
  sendSignal("setKeyboardActive", FLEX_ARG(FLEX_BOOL(active)));
}
void PanelItem::setKeymap(std::string data) {
  sendSignal("setKeymap", FLEX_ARG(FLEX_STRING(data)));
}
void PanelItem::setKeyState(uint32_t key, bool state) {
  sendSignal("setKeyState", FLEX_ARGS(FLEX_UINT(key) FLEX_UINT(state)));
}
void PanelItem::setKeyModStates(xkb_mod_mask_t depressed,
                                xkb_mod_mask_t latched, xkb_mod_mask_t locked,
                                xkb_mod_mask_t group) {
  sendSignal("setKeyModStates",
             FLEX_ARGS(FLEX_UINT(depressed) FLEX_UINT(latched) FLEX_UINT(locked)
                           FLEX_UINT(group)));
}
void PanelItem::setKeyRepeat(int32_t rate, int32_t delayMS) {
  sendSignal("setKeyRepeat", FLEX_ARGS(FLEX_INT(rate) FLEX_INT(delayMS)));
}

void PanelItem::resize(uint32_t width, uint32_t height) {
  sendSignal("resize", FLEX_ARGS(FLEX_UINT(width) FLEX_UINT(height)));
}
void PanelItem::close() { sendSignal("close", FLEX_ARG(FLEX_NULL)); }

std::vector<uint8_t> PanelItem::uiCallback(flexbuffers::Reference data, bool) {
  flexbuffers::Vector flexVec = data.AsVector();
  Item::UIEvent eventType = (Item::UIEvent)flexVec[0].AsUInt32();
  std::string nodeName = flexVec[1].AsString().str();
  flexbuffers::Vector dataVec = flexVec[2].AsVector();

  PanelItem item("/item/panel/ui", nodeName);
  switch (eventType) {
  case Item::UIEvent::Create: {
    uiCreateFunction(item, Data{dataVec[0].AsUInt32(), dataVec[1].AsUInt32()});
  } break;
  case Item::UIEvent::Capture: {
    uiCaptureFunction(item);
  } break;
  case Item::UIEvent::Release: {
    uiReleaseFunction(item, Data{dataVec[0].AsUInt32(), dataVec[1].AsUInt32()});
  } break;
  case Item::UIEvent::Destroy: {
    uiDestroyFunction(item);
  } break;
  }
  return std::vector<uint8_t>();
}

} // namespace StardustXRFusion
