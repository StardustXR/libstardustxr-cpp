#pragma once

#include <string>

namespace StardustXRFusion {

class EnvironmentInterface {
public:
	explicit EnvironmentInterface();

	void visible(bool visible);
	void setSkytex(std::string path);
	void setLighting(std::string path);
};

} // namespace StardustXRFusion
