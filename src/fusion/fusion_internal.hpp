#pragma once

#include "../messenger.hpp"
#include "scenegraph.hpp"

namespace StardustXRFusion {

extern StardustXRFusion::FusionScenegraph *scenegraph;
extern StardustXR::Messenger *messenger;

extern std::string GenerateID();

extern std::string ConvertExeRelativePath(std::string exeRelativePath);

} // namespace StardustXRFusion
