#pragma once

#include "../common/messenger.hpp"

namespace StardustXRFusion {

class Messenger : public StardustXR::Messenger {
public:
	explicit Messenger(int fd, StardustXR::Scenegraph *scenegraph);

protected:
	void onDisconnect();
};

} // namespace StardustXRFusion
