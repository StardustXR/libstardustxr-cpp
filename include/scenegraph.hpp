#ifndef STARDUSTXR_SCENEGRAPH_H
#define STARDUSTXR_SCENEGRAPH_H

#include "flatbuffers/flexbuffers.h"
#include <unistd.h>

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

#endif // STARDUSTXR_SCENEGRAPH_H
