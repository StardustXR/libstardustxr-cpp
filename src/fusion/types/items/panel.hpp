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
	static void registerUIHandler(std::function<void(bool, PanelItem &, uint32_t, uint32_t, uint32_t)> callback);

	void applySurfaceMaterial(Model &model, uint32_t submeshIndex);
	void getData(std::function<void(uint32_t, uint32_t, uint32_t)> callback);
	void resize(uint32_t width, uint32_t height);
	void close();

private:
	PanelItem(Spatial *space, std::string nodePath, std::string nodeName);
	static std::vector<uint8_t> uiCallback(flexbuffers::Reference data, bool);
	static std::function<void(bool, PanelItem &, uint32_t, uint32_t, uint32_t)> uiCallbackFunction;
};

}
