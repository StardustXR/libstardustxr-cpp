#pragma once

#include "util.hpp"
#include "message.hpp"
#include <thread>
#include <functional>

namespace StardustXR {

class Messenger {
public:
	explicit Messenger(int readFD, int writeFD);
	virtual ~Messenger();

	void sendSignal(const char *object, const char *method, ArgsConstructor argsConstructor) {
		if(checkPipeBroken()) return;
		std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
		sendSignal(object, method, data);
	}
	void sendSignal(const char *object, const char *method, std::vector<uint8_t> &data) {
		if(checkPipeBroken()) return;
		sendCall(senderBuilder, 1, 0, object, method, data);
	}

	void executeRemoteMethod(const char *object, const char *method, ArgsConstructor argsConstructor, Callback callback) {
		if(checkPipeBroken()) return;
		std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
		executeRemoteMethod(object, method, data, callback);
	}
	void executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, Callback callback);

	virtual void onPipeBreak() {}
	bool checkPipeBroken() {
		if(pipeBroke)
			onPipeBreak();
		return pipeBroke;
	}

protected:
	// General variables
	int messageReadFD;
	int messageWriteFD;
	bool pipeBroke = false;

	// Message handling specific
	std::thread handlerThread;
	flatbuffers::FlatBufferBuilder handlerBuilder;
	std::map<uint, Callback> pendingCallbacks;
	uint generateMessageID();
	virtual void messageHandler() = 0;
	virtual void handleMessage(const Message *message) = 0;

	// Message sending specific
	flatbuffers::FlatBufferBuilder senderBuilder;
	pthread_mutex_t sendLock;
	void sendCall(flatbuffers::FlatBufferBuilder &builder, uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data);
	void sendMessage(uint8_t *buffer, uint size);
};

}
