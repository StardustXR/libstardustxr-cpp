#ifndef STARDUSTXR_CLIENT_MESSENGER_H
#define STARDUSTXR_CLIENT_MESSENGER_H

#include "../messenger.hpp"
#include "../scenegraph.hpp"
#include <map>
#include <mutex>
#include <thread>

namespace StardustXR {

class ClientMessenger : public Messenger {
public:
	explicit ClientMessenger(int readFD, int writeFD, Scenegraph *scenegraph);

	void sendSignal(const char *object, const char *method, std::vector<uint8_t> &data);
	void sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data);

	flexbuffers::Reference executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data);
	void executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, void (*asyncCallback)(flexbuffers::Reference));

	void sendMessage(uint8_t *buffer, uint size);

protected:
	void messageHandler();
	void handleMessage(const Message *message);
};

} // namespace StardustXR

#endif // STARDUSTXR_CLIENT_MESSENGER_H
