#pragma once

#include <string>

#include "interfaces/environmentinterface.hpp"
#include "interfaces/lifecycleinterface.hpp"

namespace StardustXRFusion {

extern bool Setup();

extern EnvironmentInterface *Environment();
extern LifeCycleInterface *LifeCycle();

} // namespace StardustXRFusion
