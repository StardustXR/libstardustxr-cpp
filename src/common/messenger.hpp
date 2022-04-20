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

	const int fd;
	Scenegraph *const scenegraph;

	bool dispatch();

	void error(const std::string object, const std::string method, const std::string error);
	void sendSignal(const std::string object, const std::string method, ArgsConstructor argsConstructor);
	void sendSignal(const std::string object, const std::string method, std::vector<uint8_t> &data);
	void executeRemoteMethod(const std::string object, const std::string method, ArgsConstructor argsConstructor, Callback callback);
	void executeRemoteMethod(const std::string object, const std::string method, std::vector<uint8_t> &data, Callback callback);
	void executeRemoteMethod(const std::string object, const std::string method, ArgsConstructor argsConstructor, RawCallback callback);
	void executeRemoteMethod(const std::string object, const std::string method, std::vector<uint8_t> &data, RawCallback callback);
	//	std::vector<uint8_t> executeRemoteMethodSync(const std::string object, const std::string method, ArgsConstructor argsConstructor);

protected:
	// General methods
	int pollFD(short events, int timeout);

	// Message handling specific
	std::mutex pendingCallbacksMutex;
	std::map<uint, RawCallback> pendingCallbacks;
	uint generateMessageID();
	void handleMessage(const Message *message);

	// Message sending specific
	std::mutex sendMutex;
	flatbuffers::FlatBufferBuilder fbb;
	void sendCall(uint8_t type, uint id, const std::string object, const std::string method, const std::string error, std::vector<uint8_t> &data);
	void sendMessage(uint8_t *buffer, uint size);
};

}
