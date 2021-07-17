#pragma once

#include <thread>
#include <atomic>

#include "flex.hpp"
#include "message.hpp"
#include "scenegraph.hpp"

namespace StardustXR {

class Messenger {
public:
	explicit Messenger(int readFD, int writeFD, Scenegraph *scenegraph);
	virtual ~Messenger();

	void startHandler();

	void sendSignal(const char *object, const char *method, ArgsConstructor argsConstructor) {
		if(checkPipeBroken()) return;
		std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
		sendSignal(object, method, data);
	}
	void sendSignal(const char *object, const char *method, std::vector<uint8_t> &data) {
		if(checkPipeBroken()) return;
		sendCall(1, 0, object, method, data);
	}

	void executeRemoteMethod(const char *object, const char *method, ArgsConstructor argsConstructor, Callback callback) {
		if(checkPipeBroken()) return;
		std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
		executeRemoteMethod(object, method, data, callback);
	}
	void executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, Callback callback);


protected:
	// General variables
	int messageReadFD;
	int messageWriteFD;
	std::atomic<bool> pipeBroke{false};
	Scenegraph *scenegraph;

	// Message handling specific
	std::thread handlerThread;
	std::map<uint, Callback> pendingCallbacks;
	uint generateMessageID();
	void messageHandler();
	void handleMessage(const Message *message);

	// Message sending specific
	pthread_mutex_t sendLock;
	void sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data);
	void sendMessage(uint8_t *buffer, uint size);

	// Pipe
	virtual void onPipeBreak() {}
	bool checkPipeBroken() {
		if(pipeBroke)
			onPipeBreak();
		return pipeBroke;
	}
};

}
