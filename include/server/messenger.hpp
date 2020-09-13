#ifndef STARDUSTXR_SERVER_MESSENGER_H
#define STARDUSTXR_SERVER_MESSENGER_H

#include "../messenger.hpp"
#include "scenegraph.hpp"
#include <map>
#include <mutex>
#include <thread>

namespace StardustXR {

class MessengerManager;

class ServerMessenger : public Messenger {
public:
	explicit ServerMessenger(int sessionID, int readFD, int writeFD, ServerScenegraph *scenegraph, MessengerManager *manager);

	void sendSignal(const char *object, const char *method, std::vector<uint8_t> &data);
	void sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data);

	flexbuffers::Reference executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data);
	void executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, void (*asyncCallback)(flexbuffers::Reference));

	void sendMessage(uint8_t *buffer, uint size);

protected:
	void messageHandler();
	void handleMessage(const Message *message);

	int sessionID;
	ServerScenegraph *scenegraph;
	MessengerManager *manager;
};

} // namespace StardustXR

#endif // STARDUSTXR_SERVER_MESSENGER_H
