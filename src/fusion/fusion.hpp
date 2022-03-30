#pragma once

#include <functional>
#include <string>

namespace StardustXRFusion {

class Spatial;

typedef std::function<void(double, double)> LogicStepMethod;

bool Setup();
void StallMainThread();
void Shutdown(int signal);

Spatial *Root();
void SetSkytex(std::string path);
void SetSkylight(std::string path);
void OnLogicStep(LogicStepMethod method);

std::string ConvertExeRelativePath(std::string path);

} // namespace StardustXRFusion
