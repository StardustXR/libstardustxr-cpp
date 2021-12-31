#pragma once

#include "../acceptor.hpp"
#include "../item.hpp"
#include "../types/panel.hpp"

#include <functional>

namespace StardustXRFusion {

class PanelItemAcceptor : public ItemAcceptor {
public:
	PanelItemAcceptor(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation);

	std::function<void(PanelItem &panel, PanelItem::Data data)> itemCapturedMethod = [](PanelItem &, PanelItem::Data) {};
	std::function<void(PanelItem &panel)> itemReleasedMethod = [](PanelItem &) {};

private:
	std::vector<uint8_t> acceptorCallback(flexbuffers::Reference data, bool);
};

}
