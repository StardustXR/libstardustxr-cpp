#pragma once

#include "flatbuffers/flexbuffers.h"
#include <unistd.h>

namespace StardustXR {

class ServerScenegraph {
public:
	ServerScenegraph(){};
	virtual ~ServerScenegraph(){};

	virtual void sendSignal(int sessionID, std::string path, std::string method, flexbuffers::Reference data) {
		executeMethod(sessionID, path, method, data);
	}
	virtual std::vector<uint8_t> executeMethod(int sessionID, std::string path, std::string method, flexbuffers::Reference args) = 0;

	virtual void handleMessengerDeletion(uint sessionID) {}
};

} // namespace StardustXR
