#include "server/server_messenger.hpp"

namespace StardustXR {

ServerMessenger::ServerMessenger(int readFD, int writeFD, ServerScenegraph *scenegraph) : Messenger(readFD, writeFD) {
	this->handlerThread = std::thread(&StardustXR::ServerMessenger::messageHandler, this);
	this->scenegraph = scenegraph;
}

void ServerMessenger::sendSignal(const char *object, const char *method, std::vector<uint8_t> &data) {
	sendCall(1, 0, object, method, data);
}

flexbuffers::Reference ServerMessenger::executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data) {
	uint id = generateMessageID();
	sendCall(2, id, object, method, data);
	syncMethodMutex.lock();
	syncMethodMutex.unlock();
	relockMutex = true;
	return pendingMessageReturn;
}

void ServerMessenger::sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data) {
	builder.Clear();

	auto objectPath = builder.CreateString(object);
	auto methodName = builder.CreateString(method);
	auto dataBuffer = builder.CreateVector<uint8_t>(data);

	MessageBuilder messageBuilder(builder);
	messageBuilder.add_type(type);
	messageBuilder.add_id(id);
	messageBuilder.add_object(objectPath);
	messageBuilder.add_method(methodName);
	messageBuilder.add_data(dataBuffer);
	auto message = messageBuilder.Finish();

	builder.Finish(message);
	sendMessage(builder.GetBufferPointer(), builder.GetSize());
}

void ServerMessenger::sendMessage(uint8_t *buffer, uint32_t size) {
	write(messageWriteFD, &size, 4);
	write(messageWriteFD, buffer, size);
}

void ServerMessenger::messageHandler() {
	syncMethodMutex.lock();
	while (true) {
		if (relockMutex) {
			syncMethodMutex.lock();
			relockMutex = false;
		}

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
		scenegraph->sendSignal(message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
	} break;
	case 2: {
		std::vector<uint8_t> returnValue = scenegraph->executeMethod(message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
		sendCall(3, 0, message->object()->c_str(), message->method()->c_str(), returnValue);
	} break;
	case 3: {
		pendingMessageReturn = message->data_flexbuffer_root();
		syncMethodMutex.unlock();
	}
	}
}

} // namespace StardustXR
