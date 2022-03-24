#pragma once

#include <atomic>
#include <mutex>
#include <thread>

#include "flatbuffers/message.hpp"
#include "flex.hpp"
#include "scenegraph.hpp"

namespace StardustXR {

class Messenger {
public:
	Messenger(int fd, Scenegraph *scenegraph);
	virtual ~Messenger();

	void startHandler();

	void error(const std::string object, const std::string method, const std::string error);
	void sendSignal(const std::string object, const std::string method, ArgsConstructor argsConstructor) {
		std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
		sendSignal(object, method, data);
	}
	void sendSignal(const std::string object, const std::string method, std::vector<uint8_t> &data) {
		sendCall(1, 0, object, method, "", data);
	}

	void executeRemoteMethod(const std::string object, const std::string method, ArgsConstructor argsConstructor, Callback callback) {
		std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
		executeRemoteMethod(object, method, data, callback);
	}
	void executeRemoteMethod(const std::string object, const std::string method, std::vector<uint8_t> &data, Callback callback);

protected:
	// General variables
	int fd;
	Scenegraph *scenegraph;

	// General methods
	int pollFD(short events, int timeout);
	virtual void onDisconnect() {}

	// Message handling specific
	std::thread handlerThread;
	std::mutex pendingCallbacksMutex;
	std::map<uint, Callback> pendingCallbacks;
	uint generateMessageID();
	void messageHandler();
	void handleMessage(const Message *message);

	// Message sending specific
	std::mutex sendMutex;
	flatbuffers::FlatBufferBuilder fbb;
	void sendCall(uint8_t type, uint id, const std::string object, const std::string method, const std::string error, std::vector<uint8_t> &data);
	void sendMessage(uint8_t *buffer, uint size);
};

}
