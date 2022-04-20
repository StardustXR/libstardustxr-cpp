#pragma once

#include <functional>
#include <string>

namespace StardustXRFusion {

class Spatial;

typedef std::function<void(double, double)> LogicStepMethod;

bool Setup();
void RunEventLoop(int timeout = 10000);
//void Stop();

Spatial *Root();
void SetSkytex(std::string path);
void SetSkylight(std::string path);
void OnLogicStep(LogicStepMethod method);

std::string ConvertExeRelativePath(std::string path);

} // namespace StardustXRFusion
