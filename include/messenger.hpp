#ifndef STARDUSTXR_MESSENGER_H
#define STARDUSTXR_MESSENGER_H

#include "message.hpp"
#include "scenegraph.hpp"
#include <thread>
#include <mutex>

namespace StardustXR {

typedef struct pending_message {
	const Message *message;
	std::mutex mutex;
} PendingMessage;

class Messenger {
public:
	explicit Messenger(int readFD, int writeFD, Scenegraph *scenegraph);

protected:
	int messageReadFD;
	int messageWriteFD;
	flatbuffers::FlatBufferBuilder builder;

	Scenegraph *scenegraph;

	uint32_t pendingMessageID;
	flexbuffers::Reference pendingMessageReturn;
	std::mutex syncMethodMutex;
	bool relockMutex = false;
	std::thread handlerThread;

	uint generateMessageID();
	void messageHandler();
	void handleMessage(const Message *message);
};

}

#endif // STARDUSTXR_SCENEGRAPH_H
