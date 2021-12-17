#include "messenger.hpp"

namespace StardustXRFusion {

Messenger::Messenger(int fd, StardustXR::Scenegraph *scenegraph) : StardustXR::Messenger(fd, scenegraph) {}

void Messenger::onDisconnect() {
	std::exit(EXIT_FAILURE);
}

} // namespace StardustXRFusion
