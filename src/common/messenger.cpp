#include "messenger.hpp"
#include <flatbuffers/flatbuffers.h>
#include <mutex>
#include <poll.h>
#include <unistd.h>

namespace StardustXR {

Messenger::Messenger(int fd, Scenegraph *scenegraph) {
	this->fd = fd;
	this->scenegraph = scenegraph;
}
Messenger::~Messenger() {}

void Messenger::startHandler() {
	this->handlerThread = std::thread(&StardustXR::Messenger::messageHandler, this);
	this->handlerThread.detach();
}

void Messenger::error(const std::string object, const std::string method, const std::string error) {
	std::vector<uint8_t> blankData;
	sendCall(0, 0, object, method, error, blankData);
}

uint Messenger::generateMessageID() {
	const std::lock_guard<std::mutex> lock(pendingCallbacksMutex);

	uint id = 0;
	while(pendingCallbacks.count(id)) //Increment up until a free spot is found for the message ID
		id++;
	return id;
}

void Messenger::executeRemoteMethod(const std::string object, const std::string method, std::vector<uint8_t> &data, Callback callback) {
	uint id = generateMessageID();
	{
		const std::lock_guard<std::mutex> lock(pendingCallbacksMutex);
		pendingCallbacks[id] = callback;
	}
	sendCall(2, id, object, method, "", data);
}

int Messenger::pollFD(short events, int timeout) {
	struct pollfd poll_fds[1];
	poll_fds[0].fd = fd;
	poll_fds[0].events = events;

	return poll(poll_fds, 1, timeout);
}

void Messenger::sendCall(uint8_t type, uint id, const std::string object, const std::string method, const std::string error, std::vector<uint8_t> &data) {
	const std::lock_guard<std::mutex> sendLock(sendMutex);

	auto objectPath   = fbb.CreateString(object);
	auto methodName   = fbb.CreateString(method);
	auto errorMessage = fbb.CreateString(error);
	auto dataBuffer   = fbb.CreateVector<uint8_t>(data);

	MessageBuilder messageBuilder(fbb);
	messageBuilder.add_type(type);
	messageBuilder.add_id(id);
	messageBuilder.add_object(objectPath);
	messageBuilder.add_method(methodName);
	messageBuilder.add_error(errorMessage);
	messageBuilder.add_data(dataBuffer);
	auto message = messageBuilder.Finish();

	fbb.Finish(message);
	sendMessage(fbb.GetBufferPointer(), fbb.GetSize());
	fbb.Clear();
}

void Messenger::sendMessage(uint8_t *buffer, uint32_t size) {
	int rv = pollFD(POLLOUT, 1);
	if(rv <= 0)
		return;
	ssize_t rc;
	rc = write(fd, &size, 4);
	if (rc == -1 && errno == EPIPE) {
//		onSocketBreak();
		return;
	}

	write(fd, buffer, size);
}

void Messenger::messageHandler() {
	while (1) {
		int rv = 0;
		while(rv <= 0) {
			if(rv == -1) {
				onDisconnect();
				return;
			}
			rv = pollFD(POLLIN, 100);
		}

		uint32_t messageLength;
		switch (read(fd, &messageLength, 4)) {
			case 0: {
				printf("Pipe broke!\n");
				onDisconnect();
				return;
			} break;
			case -1: {
				printf("Pipe error\n");
				onDisconnect();
				continue;
			}
		}

		uint8_t *messageBinary = (uint8_t *) malloc(messageLength);
		read(fd, messageBinary, messageLength);

		flatbuffers::Verifier messageVerifier(messageBinary, messageLength);
		if(VerifyMessageBuffer(messageVerifier)) {
			const Message *message = GetMessage(messageBinary);
			handleMessage(message);
		}

		free(messageBinary);
	}
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
		sendCall(3, message->id(), message->object()->str(), message->method()->str(), "", returnValue);
	} break;
	case 3: {
		Callback callback = nullptr;
		{
			const std::lock_guard<std::mutex> lock(pendingCallbacksMutex);
			if(pendingCallbacks.count(message->id())) {
				callback = pendingCallbacks[message->id()];
				pendingCallbacks.erase(message->id());
			} else {
				// I have no idea how this would happen but I don't want anything breaking on the slim chance it does...
				printf("The method callback \"%s\" on object with path \"%s\" and id %i is not pending\n", message->method()->c_str(), message->object()->c_str(), message->id());
				return;
			}
		}

		//Method return, so execute the callback method if it exists and remove it from the pending map
		callback(message->data_flexbuffer_root());
	}
	}
}

} // namespace StardustXR
