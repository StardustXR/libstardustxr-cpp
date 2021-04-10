#pragma once

#include <string>

#include "../client/messenger.hpp"

#include "scenegraph.hpp"
#include "interfaces/lifecycleinterface.hpp"

namespace StardustXRFusion {

extern StardustXRFusion::FusionScenegraph *scenegraph;
extern StardustXR::ClientMessenger *messenger;

extern std::string GenerateID();
extern bool Setup();

extern LifeCycleInterface *LifeCycle();

} // namespace StardustXRFusion
