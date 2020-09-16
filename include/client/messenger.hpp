#ifndef STARDUSTXR_CLIENT_MESSENGER_H
#define STARDUSTXR_CLIENT_MESSENGER_H

#include "../messenger.hpp"
#include "scenegraph.hpp"
#include <map>
#include <mutex>
#include <thread>

namespace StardustXR {

class ClientMessenger : public Messenger {
public:
	explicit ClientMessenger(int readFD, int writeFD, ClientScenegraph *scenegraph);

	void sendSignal(const char *object, const char *method, ArgsConstructor argsConstructor) {
		std::vector<uint8_t> data = constructArguments(argsConstructor);
		sendSignal(object, method, data);
	}
	void sendSignal(const char *object, const char *method, std::vector<uint8_t> &data) {
		sendCall(1, 0, object, method, data);
	}

	flexbuffers::Reference executeRemoteMethod(const char *object, const char *method, ArgsConstructor argsConstructor) {
		std::vector<uint8_t> data = constructArguments(argsConstructor);
		return executeRemoteMethod(object, method, data);
	}
	flexbuffers::Reference executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data);

	void executeRemoteMethod(const char *object, const char *method, ArgsConstructor argsConstructor, Callback callback) {
		std::vector<uint8_t> data = constructArguments(argsConstructor);
		executeRemoteMethod(object, method, data, callback);
	}
	void executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, Callback callback);

	void sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data);
	void sendMessage(uint8_t *buffer, uint size);

protected:
	void messageHandler();
	void handleMessage(const Message *message);
	std::vector<uint8_t> constructArguments(ArgsConstructor argsConstructor) {
		flexbuffers::Builder fbb;
		argsConstructor(fbb);
		fbb.Finish();
		return fbb.GetBuffer();
	}

	ClientScenegraph *scenegraph;
};

} // namespace StardustXR

#endif // STARDUSTXR_CLIENT_MESSENGER_H
