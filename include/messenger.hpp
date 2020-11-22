#ifndef LIBSTARDUSTXR_MESSENGER_H
#define LIBSTARDUSTXR_MESSENGER_H

#include "util.hpp"
#include "message.hpp"
#include <thread>
#include <mutex>
#include <functional>

namespace StardustXR {

class Messenger {
public:
	explicit Messenger(int readFD, int writeFD);
	virtual ~Messenger();

	void sendSignal(const char *object, const char *method, ArgsConstructor argsConstructor) {
		std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
		sendSignal(object, method, data);
	}
	void sendSignal(const char *object, const char *method, std::vector<uint8_t> &data) {
		sendCall(1, 0, object, method, data);
	}

	void executeRemoteMethod(const char *object, const char *method, ArgsConstructor argsConstructor, Callback callback) {
		std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
		executeRemoteMethod(object, method, data, callback);
	}
	void executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, Callback callback);

protected:
	// General variables
	int messageReadFD;
	int messageWriteFD;

	// Message handling specific
	std::thread handlerThread;
	flatbuffers::FlatBufferBuilder builder;
	std::map<uint, Callback> pendingCallbacks;
	uint generateMessageID();
	virtual void messageHandler() = 0;
	virtual void handleMessage(const Message *message) = 0;

	// Message sending specific
	void sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data);
	void sendMessage(uint8_t *buffer, uint size);
};

}

#endif // LIBSTARDUSTXR_SCENEGRAPH_H
