#include "scenegraph.hpp"

namespace StardustXRFusion {

FusionScenegraph::FusionScenegraph() {}

void FusionScenegraph::sendSignal(std::string, std::string methodName, flexbuffers::Reference data) {
	Method *method = &methods[methodName];
	(*method)(data, false);
}

std::vector<uint8_t> FusionScenegraph::executeMethod(std::string, std::string methodName, flexbuffers::Reference data) {
	Method *method = &methods[methodName];
	return (*method)(data, true);
}

} // namespace StardustXRFusion
