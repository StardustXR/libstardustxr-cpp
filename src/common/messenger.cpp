#include "messenger.hpp"
#include <flatbuffers/flatbuffers.h>
#include <mutex>
#include <future>
#include <poll.h>
#include <unistd.h>

namespace StardustXR {

Messenger::Messenger(int fd, Scenegraph *scenegraph) :
fd(fd),
scenegraph(scenegraph) {}

uint Messenger::generateMessageID() {
	const std::lock_guard<std::mutex> lock(pendingCallbacksMutex);

	uint id = 0;
	while(pendingCallbacks.count(id)) //Increment up until a free spot is found for the message ID
		id++;
	return id;
}
int Messenger::pollFD(short events, int timeout) {
	pollfd poll_fd {
		.fd = fd,
		.events = events,
	};
	return poll(&poll_fd, 1, timeout);
}

void Messenger::error(const std::string object, const std::string method, const std::string error) {
	std::vector<uint8_t> blankData;
	sendCall(0, 0, object, method, error, blankData);
}

void Messenger::sendSignal(const std::string object, const std::string method, ArgsConstructor argsConstructor) {
	std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
	sendSignal(object, method, data);
}
void Messenger::sendSignal(const std::string object, const std::string method, std::vector<uint8_t> &data) {
	sendCall(1, 0, object, method, "", data);
}

void Messenger::executeRemoteMethod(const std::string object, const std::string method, ArgsConstructor argsConstructor, Callback callback) {
	executeRemoteMethod(object, method, argsConstructor, [callback](const std::vector<uint8_t> data) {
		flexbuffers::Reference flex = flexbuffers::GetRoot(data);
		callback(flex);
	});
}
void Messenger::executeRemoteMethod(const std::string object, const std::string method, std::vector<uint8_t> &data, Callback callback) {
	executeRemoteMethod(object, method, data, [callback](const std::vector<uint8_t> data) {
		flexbuffers::Reference flex = flexbuffers::GetRoot(data);
		callback(flex);
	});
}
void Messenger::executeRemoteMethod(const std::string object, const std::string method, ArgsConstructor argsConstructor, RawCallback callback) {
	std::vector<uint8_t> data = FlexbufferFromArguments(argsConstructor);
	executeRemoteMethod(object, method, data, callback);
}
void Messenger::executeRemoteMethod(const std::string object, const std::string method, std::vector<uint8_t> &data, RawCallback callback) {
	uint id = generateMessageID();
	{
		const std::lock_guard<std::mutex> lock(pendingCallbacksMutex);
		pendingCallbacks[id] = callback;
	}
	sendCall(2, id, object, method, "", data);
}

//std::vector<uint8_t> Messenger::executeRemoteMethodSync(const std::string object, const std::string method, ArgsConstructor argsConstructor) {
//	std::promise<std::vector<uint8_t>> promise;
//	std::future<std::vector<uint8_t>> future = promise.get_future();
//	executeRemoteMethod(object, method, argsConstructor, [&promise](const std::vector<uint8_t> data) {
//		promise.set_value(data);
//	});
//	return future.get();
//}

void Messenger::sendCall(uint8_t type, uint id, const std::string object, const std::string method, const std::string error, std::vector<uint8_t> &data) {
	const std::lock_guard<std::mutex> sendLock(sendMutex);
	fbb.Clear();

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
}

void Messenger::sendMessage(uint8_t *buffer, uint32_t size) {
	int rv = pollFD(POLLOUT, 0);
	if(rv <= 0) return;

	ssize_t rc = write(fd, &size, 4);
	if (rc != 4) return;

	write(fd, buffer, size);
}

bool Messenger::dispatch() {
	uint32_t messageLength;
	if(read(fd, &messageLength, 4) != 4)
		return false;

	uint8_t *messageBinary = (uint8_t *)malloc(messageLength);
	if(read(fd, messageBinary, messageLength) != messageLength)
		return false;

	flatbuffers::Verifier messageVerifier(messageBinary, messageLength);
	if(VerifyMessageBuffer(messageVerifier)) {
		const Message *message = GetMessage(messageBinary);
		handleMessage(message);
	}

	free(messageBinary);
	return true;
}

void Messenger::handleMessage(const Message *message) {
	switch (message->type()) {
		case 0: {
			// Error, so spit the error out to stderr
			fprintf(stderr, "[Stardust XR][%s:%s] %s\n", message->object()->c_str(), message->method()->c_str(), message->error()->c_str());
		} break;
		case 1: {
			// Signal, so execute the local scenegraph method
			flexbuffers::Reference dataRoot = flexbuffers::GetRoot(message->data()->Data(), message->data()->Length());
			scenegraph->sendSignal(message->object()->str(), message->method()->str(), dataRoot);
		} break;
		case 2: {

			// Method was called, so execute the local scenegraph method and send back the result
			flexbuffers::Reference dataRoot = flexbuffers::GetRoot(message->data()->Data(), message->data()->Length());
			std::vector<uint8_t> returnValue = scenegraph->executeMethod(message->object()->str(), message->method()->str(), dataRoot);
			sendCall(3, message->id(), message->object()->str(), message->method()->str(), "", returnValue);
		} break;
		case 3: {
			RawCallback callback = nullptr;
			std::unique_lock<std::mutex> lock(pendingCallbacksMutex);
			if(pendingCallbacks.count(message->id())) {
				callback = pendingCallbacks[message->id()];
				pendingCallbacks.erase(message->id());
			} else {
				// I have no idea how this would happen but I don't want anything breaking on the slim chance it does...
				printf("The method callback on node \"%s\" with method \"%s\" and id %i is not pending\n", message->object()->c_str(), message->method()->c_str(), message->id());
				return;
			}
			lock.unlock();

			//Method return, so execute the callback method if it exists and remove it from the pending map
			callback(std::vector<uint8_t>(message->data()->Data(), message->data()->Data() + message->data()->size()));
		} break;
	}
}

} // namespace StardustXR
