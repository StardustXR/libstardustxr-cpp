#pragma once

#include <functional>
#include <map>
#include <mutex>
#include "../common/scenegraph.hpp"

#define FUSION_SCENEGRAPH_METHOD(method_name, method_ref) scenegraph->methods[method_name] = std::bind(method_ref, this, std::placeholders::_1, std::placeholders::_2);

namespace StardustXRFusion {

typedef std::function<std::vector<uint8_t>(flexbuffers::Reference, bool)> Method;

class FusionScenegraph : public StardustXR::Scenegraph {
public:
	explicit FusionScenegraph();

	void addMethod(std::string name, Method method);
	void removeMethod(std::string name);

	void sendSignal(std::string nodePath, std::string methodName, flexbuffers::Reference data);
	std::vector<uint8_t> executeMethod(std::string nodePath, std::string methodName, flexbuffers::Reference data);
protected:
	std::mutex methodsMutex;
	std::map<std::string, Method> methods;
};

} // namespace StardustXRFusion
