#include "scenegraph.hpp"
#include <cstdint>

namespace StardustXRFusion {

FusionScenegraph::FusionScenegraph() {}

void FusionScenegraph::sendSignal(std::string, std::string methodName, flexbuffers::Reference data) {
	if(methods.find(methodName) != methods.end()) {
		Method *method = &methods[methodName];
		(void)(*method)(data, false);
	} else {
		fprintf(stderr, "Client method \"%s\" does not exist", methodName.c_str());
	}
}

std::vector<uint8_t> FusionScenegraph::executeMethod(std::string, std::string methodName, flexbuffers::Reference data) {
	if(methods.find(methodName) != methods.end()) {
		Method *method = &methods[methodName];
		return (*method)(data, false);
	} else {
		fprintf(stderr, "Client method \"%s\" does not exist", methodName.c_str());
		return std::vector<uint8_t>();
	}
}

} // namespace StardustXRFusion
