#pragma once

#include <functional>
#include <string>

namespace StardustXRFusion {

class Spatial;

typedef std::function<void(double, double)> LogicStepMethod;

extern bool Setup();
extern void StallMainThread();
extern void Shutdown(int signal);

extern Spatial *Root();
extern void SetSkytex(std::string path);
extern void SetSkylight(std::string path);
extern void OnLogicStep(LogicStepMethod method);

} // namespace StardustXRFusion
