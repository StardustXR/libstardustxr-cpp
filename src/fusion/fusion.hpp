#pragma once

#include <string>

#include "interfaces/environmentinterface.hpp"
#include "interfaces/lifecycleinterface.hpp"

namespace StardustXRFusion {

extern bool Setup();
extern void Shutdown();

extern EnvironmentInterface *Environment();
extern LifeCycleInterface *LifeCycle();

} // namespace StardustXRFusion
