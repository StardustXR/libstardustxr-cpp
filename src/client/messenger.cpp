#include "client/messenger.hpp"

namespace StardustXR {

ClientMessenger::ClientMessenger(int readFD, int writeFD, ClientScenegraph *scenegraph) : Messenger(readFD, writeFD) {
	this->handlerThread = std::thread(&StardustXR::ClientMessenger::messageHandler, this);
	this->scenegraph = scenegraph;
}

void ClientMessenger::messageHandler() {
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

void ClientMessenger::handleMessage(const Message *message) {
	switch (message->type()) {
	case 0: {
		fputs(message->error()->c_str(), stderr);
	} break;
	case 1: {
		scenegraph->sendSignal(message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
	} break;
	case 2: {
		std::vector<uint8_t> returnValue = scenegraph->executeMethod(message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
		sendCall(3, 0, message->object()->c_str(), message->method()->c_str(), returnValue);
	} break;
	// case 3: {
	// }
	}
}
} // namespace StardustXR
