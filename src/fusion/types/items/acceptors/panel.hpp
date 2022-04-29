#pragma once

#include "../acceptor.hpp"
#include "../item.hpp"
#include "../types/panel.hpp"

#include <functional>

namespace StardustXRFusion {

class PanelItemAcceptor : public ItemAcceptor {
public:
	explicit PanelItemAcceptor(Spatial *parent, Field &field, Vec3 origin, Quat rotation);

	std::function<void(PanelItem &panel, PanelItem::Data data)> itemCapturedMethod = [](PanelItem &, PanelItem::Data) {};
	std::function<void(PanelItem &panel)> itemReleasedMethod = [](PanelItem &) {};

private:
	std::vector<uint8_t> acceptorCallback(flexbuffers::Reference data, bool);
};

}
