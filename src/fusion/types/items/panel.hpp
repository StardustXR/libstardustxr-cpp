#pragma once

#include "item.hpp"
#include "../model.hpp"
#include <functional>
#include <string>
#include <vector>

namespace flexbuffers {
	class Reference;
}

namespace StardustXRFusion {

class PanelItem : public Item {
public:
	static void registerUIHandler(std::function<void(bool, PanelItem &, uint32_t, uint32_t)> callback);

	void applySurfaceMaterial(Model &model, uint32_t submeshIndex);
	void getData(std::function<void(uint32_t, uint32_t)> callback);

	void setPointerActive(bool active);
	void setPointerPosition(SKMath::vec2 pos);
	void setPointerButtonPressed(uint32_t button, bool pressed);
	void scrollPointerAxis(uint32_t source, double x, double y, int32_t dx, int32_t dy);

	void touchDown(uint32_t id, double x, double y);
	void touchMove(uint32_t id, double x, double y);
	void touchUp(uint32_t id);

	void resize(uint32_t width, uint32_t height);
	void close();

private:
	PanelItem(Spatial *space, std::string nodePath, std::string nodeName);
	static std::vector<uint8_t> uiCallback(flexbuffers::Reference data, bool);
	static std::function<void(bool, PanelItem &, uint32_t, uint32_t)> uiCallbackFunction;
};

}
