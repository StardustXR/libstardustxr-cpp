#ifndef LIBSTARDUSTXR_SERVER_MESSENGER_H
#define LIBSTARDUSTXR_SERVER_MESSENGER_H

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

protected:
	void messageHandler();
	void handleMessage(const Message *message);

	int sessionID;
	ServerScenegraph *scenegraph;
	MessengerManager *manager;
};

} // namespace StardustXR

#endif // LIBSTARDUSTXR_SERVER_MESSENGER_H
