#include "client/messenger.hpp"

namespace StardustXR {

ClientMessenger::ClientMessenger(int readFD, int writeFD, ClientScenegraph *scenegraph) : Messenger(readFD, writeFD) {
	this->scenegraph = scenegraph;
}

void ClientMessenger::startHandler() {
	this->handlerThread = std::thread(&StardustXR::ClientMessenger::messageHandler, this);
}

void ClientMessenger::messageHandler() {
	while (true) {
		uint32_t messageLength;
		if (read(messageReadFD, &messageLength, 4) == 0) {
			printf("Pipe broke!\n");
			pipeBroke = true;
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
		// Error, so spit the error out to stderr
		fputs(message->error()->c_str(), stderr);
	} break;
	case 1: {
		// Signal, so execute the local scenegraph method
		scenegraph->sendSignal(message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
	} break;
	case 2: {
		// Method was called, so execute the local scenegraph method and send back the result
		std::vector<uint8_t> returnValue = scenegraph->executeMethod(message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
		sendCall(handlerBuilder, 3, message->id(), message->object()->c_str(), message->method()->c_str(), returnValue);
	} break;
	case 3: {
		//Method return, so execute the callback method if it exists and remove it from the pending map
		if(pendingCallbacks.count(message->id())) {
			pendingCallbacks[message->id()](message->data_flexbuffer_root());
			pendingCallbacks.erase(message->id());
		} else {
			// I have no idea how this would happen but I don't want anything breaking on the slim chance it does...
			printf("The method callback \"%s\" on object with path \"%s\" and id %i is not pending\n", message->method()->c_str(), message->object()->c_str(), message->id());
		}
	}
	}
}

} // namespace StardustXR
