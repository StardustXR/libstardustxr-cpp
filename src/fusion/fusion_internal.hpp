#pragma once

#include "fusion.hpp"

#include "messenger.hpp"
#include "scenegraph.hpp"

namespace StardustXRFusion {

extern StardustXRFusion::FusionScenegraph *scenegraph;
extern StardustXRFusion::Messenger *messenger;

std::string GenerateID();
void Shutdown();

bool FileExists(std::string path);

} // namespace StardustXRFusion
