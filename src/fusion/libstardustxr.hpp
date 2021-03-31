#pragma once

#include "../client/messenger.hpp"
#include "scenegraph.hpp"

namespace StardustXRFusion {

static FusionScenegraph *scenegraph = nullptr;
static StardustXR::ClientMessenger *messenger = nullptr;

inline std::string GenerateID() {
	char *id = nullptr;
	sprintf(id, "%ld", time(nullptr));
	return std::string(id);
}

}
