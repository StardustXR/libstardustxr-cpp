#pragma once

#include "../messenger.hpp"
#include "../scenegraph.hpp"
#include <map>
#include <mutex>
#include <signal.h>
#include <thread>

namespace StardustXR {

class MessengerManager;

class ServerMessenger : public Messenger {
public:
	explicit ServerMessenger(int readFD, int writeFD, Scenegraph *scenegraph);

	void startHandler();

protected:
	void messageHandler();
	void handleMessage(const Message *message);

	virtual void onPipeBreak() = 0;
	Scenegraph *scenegraph;
};

} // namespace StardustXR
