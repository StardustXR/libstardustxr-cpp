#pragma once

#include "messenger.hpp"
#include "scenegraph.hpp"

namespace StardustXRFusion {

extern StardustXRFusion::FusionScenegraph *scenegraph;
extern StardustXRFusion::Messenger *messenger;

extern std::string GenerateID();

extern bool FileExists(std::string path);
extern std::string ConvertExeRelativePath(std::string path);

} // namespace StardustXRFusion
