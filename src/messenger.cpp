#include "messenger.hpp"
#include <flatbuffers/flatbuffers.h>
#include <mutex>
#include <signal.h>
#include <unistd.h>

namespace StardustXR {

Messenger::Messenger(int readFD, int writeFD, Scenegraph *scenegraph) {
	this->messageReadFD = readFD;
	this->messageWriteFD = writeFD;
	this->scenegraph = scenegraph;

	// setup signal handler
	struct sigaction sigact = {SIG_IGN};
	sigaction(SIGPIPE, &sigact, nullptr);
}

Messenger::~Messenger() {}

void Messenger::startHandler() {
	this->handlerThread = std::thread(&StardustXR::Messenger::messageHandler, this);
	this->handlerThread.detach();
}

uint Messenger::generateMessageID() {
	uint id = 0;
	while(pendingCallbacks.count(id)) //Increment up until a free spot is found for the message ID
		id++;
	return id;
}

void Messenger::executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, Callback callback) {
	if(checkPipeBroken()) return;
	uint id = generateMessageID();
	pendingCallbacks[id] = callback;
	sendCall(2, id, object, method, data);
}

void Messenger::sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data) {
	if(checkPipeBroken()) return;
	flatbuffers::FlatBufferBuilder builder;

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

void Messenger::sendMessage(uint8_t *buffer, uint32_t size) {
	const std::lock_guard<std::mutex> lock(sendMutex);

	ssize_t rc;
	rc = write(messageWriteFD, &size, 4);
	if (rc == -1 && errno == EPIPE) {
		pipeBroke = true;
		checkPipeBroken();
	}

	write(messageWriteFD, buffer, size);
}

void Messenger::messageHandler() {
	while (!pipeBroke) {
		uint32_t messageLength;
		if (read(messageReadFD, &messageLength, 4) == 0) {
			printf("Pipe broke!\n");
			pipeBroke = true;
			continue;
		}

		void *messageBinary = malloc(messageLength);
		read(messageReadFD, messageBinary, messageLength);

		const Message *message = GetMessage(messageBinary);
		handleMessage(message);

		free(messageBinary);
	}

	onPipeBreak();
}

void Messenger::handleMessage(const Message *message) {
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
		sendCall(3, message->id(), message->object()->c_str(), message->method()->c_str(), returnValue);
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
