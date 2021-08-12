#include "environmentinterface.hpp"
#include "../flex.hpp"
#include "../fusion_internal.hpp"

namespace StardustXRFusion {

EnvironmentInterface::EnvironmentInterface() {}

void EnvironmentInterface::visible(bool visible) {
	messenger->sendSignal(
		"/environment",
		"visible",
		FLEX_ARG(
			FLEX_BOOL(visible)
		)
	);
}

void EnvironmentInterface::setSkytex(std::string path) {
	if(!FileExists(path))
		return;
	messenger->sendSignal(
		"/environment",
		"setSkytex",
		FLEX_ARG(
			FLEX_STRING(ConvertExeRelativePath(path))
		)
	);
}

void EnvironmentInterface::setLighting(std::string path) {
	if(!FileExists(path))
		return;
	messenger->sendSignal(
		"/environment",
		"setLighting",
		FLEX_ARG(
			FLEX_STRING(ConvertExeRelativePath(path))
		)
	);
}

} // namespace StardustXRFusion
