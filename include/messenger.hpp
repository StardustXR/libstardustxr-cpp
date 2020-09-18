#ifndef STARDUSTXR_MESSENGER_H
#define STARDUSTXR_MESSENGER_H

#include "message.hpp"
#include <thread>
#include <mutex>

namespace StardustXR {

class Messenger {
public:
	explicit Messenger(int readFD, int writeFD);
	virtual ~Messenger();

	typedef std::function<void(flexbuffers::Builder&)> ArgsConstructor;
	typedef std::function<void(flexbuffers::Reference)> Callback;

	void sendSignal(const char *object, const char *method, ArgsConstructor argsConstructor) {
		std::vector<uint8_t> data = constructArguments(argsConstructor);
		sendSignal(object, method, data);
	}
	void sendSignal(const char *object, const char *method, std::vector<uint8_t> &data) {
		sendCall(1, 0, object, method, data);
	}

	void executeRemoteMethod(const char *object, const char *method, ArgsConstructor argsConstructor, Callback callback) {
		std::vector<uint8_t> data = constructArguments(argsConstructor);
		executeRemoteMethod(object, method, data, callback);
	}
	void executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, Callback callback);

protected:
	int messageReadFD;
	int messageWriteFD;
	flatbuffers::FlatBufferBuilder builder;

	std::thread handlerThread;

	uint generateMessageID();
	virtual void messageHandler() = 0;
	virtual void handleMessage(const Message *message) = 0;

	void sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data);
	void sendMessage(uint8_t *buffer, uint size);

	std::vector<uint8_t> constructArguments(ArgsConstructor argsConstructor) {
		flexbuffers::Builder fbb;
		argsConstructor(fbb);
		fbb.Finish();
		return fbb.GetBuffer();
	}
};

}

#endif // STARDUSTXR_SCENEGRAPH_H
