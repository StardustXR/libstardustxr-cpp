#pragma once

#include "fusion.hpp"

#include "messenger.hpp"
#include "scenegraph.hpp"

namespace StardustXRFusion {

extern StardustXRFusion::FusionScenegraph *scenegraph;
extern StardustXRFusion::Messenger *messenger;

std::string GenerateID();

bool FileExists(std::string path);

} // namespace StardustXRFusion
