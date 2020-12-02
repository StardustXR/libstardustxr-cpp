#include "messenger.hpp"
#include <signal.h>
#include <unistd.h>

namespace StardustXR {

Messenger::Messenger(int readFD, int writeFD) {
	this->messageReadFD = readFD;
	this->messageWriteFD = writeFD;
	this->handlerBuilder = flatbuffers::FlatBufferBuilder(1024);
	this->senderBuilder = flatbuffers::FlatBufferBuilder(1024);
	pthread_mutex_init(&sendLock, nullptr);

	// setup signal handler
	struct sigaction sigact = {SIG_IGN};
	sigaction(SIGPIPE, &sigact, nullptr);
}
Messenger::~Messenger() {
	pthread_mutex_destroy(&sendLock);
	handlerThread.detach();
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
	sendCall(senderBuilder, 2, id, object, method, data);
}

void Messenger::sendCall(flatbuffers::FlatBufferBuilder &builder, uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data) {
	if(checkPipeBroken()) return;
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

void Messenger::sendMessage(uint8_t *buffer, uint32_t size) {
	pthread_mutex_lock(&sendLock);
	ssize_t rc;
	rc = write(messageWriteFD, &size, 4);
	if (rc == -1 && errno == EPIPE) {
		pipeBroke = true;
		checkPipeBroken();
	}

	write(messageWriteFD, buffer, size);
	pthread_mutex_unlock(&sendLock);
}

} // namespace StardustXR
