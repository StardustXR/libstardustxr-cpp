#pragma once

#include "../client/messenger.hpp"
#include "scenegraph.hpp"

namespace StardustXRFusion {

extern StardustXRFusion::FusionScenegraph *scenegraph;
extern StardustXR::ClientMessenger *messenger;

extern std::string GenerateID();

extern std::string ConvertExeRelativePath(std::string exeRelativePath);

} // namespace StardustXRFusion
