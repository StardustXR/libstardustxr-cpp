#pragma once

#include "flatbuffers/flexbuffers.h"
#include <string.h>

namespace StardustXR {

class Scenegraph {
public:
	Scenegraph(){};
	virtual ~Scenegraph(){};

	virtual void sendSignal(std::string path, std::string method, flexbuffers::Reference data) {
		executeMethod(path, method, data);
	}
	virtual std::vector<uint8_t> executeMethod(std::string path, std::string method, flexbuffers::Reference args) = 0;
};

} // namespace StardustXR
