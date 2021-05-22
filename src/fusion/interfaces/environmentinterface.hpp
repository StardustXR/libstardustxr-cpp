#pragma once

#include <functional>
#include <flatbuffers/flexbuffers.h>

namespace StardustXRFusion {

typedef std::function<void(double, double)> LogicStepMethod;

class EnvironmentInterface {
public:
	explicit EnvironmentInterface();

	void visible(bool visible);
	void setSkytex(std::string path);
	void setLighting(std::string path);
};

} // namespace StardustXRFusion
