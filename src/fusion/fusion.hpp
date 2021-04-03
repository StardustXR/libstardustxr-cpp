#pragma once

#include <string>
#include "scenegraph.hpp"
#include "../client/messenger.hpp"

namespace StardustXRFusion {

extern StardustXRFusion::FusionScenegraph *scenegraph;
extern StardustXR::ClientMessenger *messenger;

extern std::string GenerateID();
extern bool Setup();

} // namespace StardustXRFusion
