#include "environmentinterface.hpp"
#include "../flex.hpp"
#include "../fusion_internal.hpp"

namespace StardustXRFusion {

EnvironmentInterface::EnvironmentInterface() {}

void EnvironmentInterface::setSkytex(std::string path) {
	if(!FileExists(path))
		return;
	messenger->sendSignal(
		"/drawable",
		"setSkytex",
		FLEX_ARG(
			FLEX_STRING(ConvertExeRelativePath(path))
		)
	);
}

void EnvironmentInterface::setSkylight(std::string path) {
	if(!FileExists(path))
		return;
	messenger->sendSignal(
		"/drawable",
		"setSkylight",
		FLEX_ARG(
			FLEX_STRING(ConvertExeRelativePath(path))
		)
	);
}

} // namespace StardustXRFusion
