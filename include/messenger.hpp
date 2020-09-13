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

	void sendSignal(const char *object, const char *method, std::vector<uint8_t> &data);
	void sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data);

	flexbuffers::Reference executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data);
	void executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, void (*asyncCallback)(flexbuffers::Reference));

	void sendMessage(uint8_t *buffer, uint size);

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
