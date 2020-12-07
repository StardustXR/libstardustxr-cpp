#ifndef LIBSTARDUSTXR_CLIENT_MESSENGER_H
#define LIBSTARDUSTXR_CLIENT_MESSENGER_H

#include "../messenger.hpp"
#include "scenegraph.hpp"
#include <map>
#include <mutex>
#include <thread>

namespace StardustXR {

class ClientMessenger : public Messenger {
public:
	explicit ClientMessenger(int readFD, int writeFD, ClientScenegraph *scenegraph);

	void startHandler();

protected:
	void messageHandler();
	void handleMessage(const Message *message);

	ClientScenegraph *scenegraph;
};

} // namespace StardustXR

#endif // LIBSTARDUSTXR_CLIENT_MESSENGER_H
