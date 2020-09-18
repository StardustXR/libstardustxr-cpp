#include "server/messenger.hpp"
#include "server/messengermanager.hpp"

namespace StardustXR {

ServerMessenger::ServerMessenger(int sessionID, int readFD, int writeFD, ServerScenegraph *scenegraph, MessengerManager *manager) : Messenger(readFD, writeFD) {
	this->handlerThread = std::thread(&StardustXR::ServerMessenger::messageHandler, this);
	this->scenegraph = scenegraph;
	this->manager = manager;
	this->sessionID = sessionID;
}

void ServerMessenger::messageHandler() {
	while (true) {
		uint32_t messageLength;
		if (read(messageReadFD, &messageLength, 4) == 0) {
			printf("Pipe broke!\n");
			return;
		}

		void *messageBinary = malloc(messageLength);
		read(messageReadFD, messageBinary, messageLength);

		const Message *message = GetMessage(messageBinary);
		handleMessage(message);

		free(messageBinary);
	}
}

void ServerMessenger::handleMessage(const Message *message) {
	switch (message->type()) {
	case 0: {
		fputs(message->error()->c_str(), stderr);
	} break;
	case 1: {
		scenegraph->sendSignal(sessionID, message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
	} break;
	case 2: {
		std::vector<uint8_t> returnValue = scenegraph->executeMethod(sessionID, message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
		sendCall(3, 0, message->object()->c_str(), message->method()->c_str(), returnValue);
	} break;
	// case 3: {
	// }
	}
}

} // namespace StardustXR
