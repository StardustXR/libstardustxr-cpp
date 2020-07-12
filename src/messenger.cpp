#include "messenger.hpp"

namespace StardustXR {

Messenger::Messenger(int readFD, int writeFD, Scenegraph *scenegraph) {
  this->messageReadFD = readFD;
  this->messageWriteFD = writeFD;
  this->scenegraph = scenegraph;
  this->builder = flatbuffers::FlatBufferBuilder(1024);

  this->handlerThread =
      std::thread(&StardustXR::Messenger::messageHandler, this);
}

uint Messenger::generateMessageID() { return pendingMessages.size(); }

void Messenger::sendSignal(const char *object, const char *method,
                           std::vector<uint8_t> &data) {
  sendCall(3, 0, object, method, data);
}

flexbuffers::Reference
Messenger::executeRemoteMethod(const char *object, const char *method,
                               std::vector<uint8_t> &data) {
  uint id = generateMessageID();
  sendCall(1, id, object, method, data);
}

void Messenger::sendCall(uint8_t type, uint id, const char *object,
                         const char *method, std::vector<uint8_t> &data) {
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

void Messenger::sendMessage(uint8_t *buffer, uint size) {
  write(messageWriteFD, &size, 4);
  write(messageWriteFD, buffer, size);
}

void Messenger::messageHandler() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  while (true) {
    uint32_t *messageLength = 0;
    read(messageReadFD, messageLength, 4);

    uint8_t *messageBinary = 0;
    read(messageReadFD, messageBinary, *messageLength);

    const Message *message = GetMessage(messageBinary);
    printf("Message recieved with type %u and id %u", message->type(),
           message->id());
  }
}

} // namespace StardustXR
