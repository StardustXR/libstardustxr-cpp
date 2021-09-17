#pragma once

#include <string>

#include "interfaces/environmentinterface.hpp"
#include "interfaces/lifecycleinterface.hpp"

namespace StardustXRFusion {

extern bool Setup();
extern void StallMainThread();
extern void Shutdown(int signal);

extern EnvironmentInterface *Environment();
extern LifeCycleInterface *LifeCycle();

} // namespace StardustXRFusion
