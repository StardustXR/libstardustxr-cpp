#pragma once

#include "../client/scenegraph.hpp"

namespace StardustXRFusion {

typedef std::function<std::vector<uint8_t>(flexbuffers::Reference, bool)> ClientMethod;

class FusionScenegraph : public StardustXR::ClientScenegraph {
public:
	explicit FusionScenegraph() {}
	~FusionScenegraph() {}

	void sendSignal(std::string, std::string, flexbuffers::Reference) {}
	std::vector<uint8_t> executeMethod(std::string, std::string, flexbuffers::Reference) {}
};

} // namespace StardustXRFusion
