#ifndef STARDUSTXR_MESSENGER_H
#define STARDUSTXR_MESSENGER_H

#include "message.hpp"
#include <thread>
#include <mutex>

namespace StardustXR {

typedef struct pending_message {
	const Message *message;
	std::mutex mutex;
} PendingMessage;

class Messenger {
public:
	explicit Messenger(int readFD, int writeFD);

	typedef std::function<void(flexbuffers::Builder&)> ArgsConstructor;
	typedef std::function<void(flexbuffers::Reference)> Callback;

protected:
	int messageReadFD;
	int messageWriteFD;
	flatbuffers::FlatBufferBuilder builder;

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
