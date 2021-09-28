#pragma once

#include <string>

namespace StardustXRFusion {

class EnvironmentInterface {
public:
	explicit EnvironmentInterface();

	void setSkytex(std::string path);
	void setSkylight(std::string path);
};

} // namespace StardustXRFusion
