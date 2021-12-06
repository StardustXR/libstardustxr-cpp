#include "scenegraph.hpp"
#include <cstdint>

namespace StardustXRFusion {

FusionScenegraph::FusionScenegraph() {}

void FusionScenegraph::addMethod(std::string name, Method method) {
	std::lock_guard<std::mutex> lock(methodsMutex);
	methods[name] = method;
}

void FusionScenegraph::removeMethod(std::string name) {
	std::lock_guard<std::mutex> lock(methodsMutex);
	auto method = methods.find(name);
	if(method != methods.end())
		methods.erase(method);
}

void FusionScenegraph::sendSignal(std::string, std::string methodName, flexbuffers::Reference data) {
	methodsMutex.lock();
	if(methods.find(methodName) != methods.end()) {
		Method *method = &methods[methodName];
		methodsMutex.unlock();
		(void)(*method)(data, false);
	} else {
		methodsMutex.unlock();
		fprintf(stderr, "Client method \"%s\" does not exist", methodName.c_str());
	}
}

std::vector<uint8_t> FusionScenegraph::executeMethod(std::string, std::string methodName, flexbuffers::Reference data) {
	methodsMutex.lock();
	if(methods.find(methodName) != methods.end()) {
		Method *method = &methods[methodName];
		methodsMutex.unlock();
		return (*method)(data, false);
	} else {
		fprintf(stderr, "Client method \"%s\" does not exist", methodName.c_str());
		methodsMutex.unlock();
		return std::vector<uint8_t>();
	}
}

} // namespace StardustXRFusion
