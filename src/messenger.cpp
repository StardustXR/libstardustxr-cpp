#include "messenger.hpp"

namespace StardustXR {

Messenger::Messenger(int readFD, int writeFD, Scenegraph *scenegraph) {
  this->messageReadFD = readFD;
  this->messageWriteFD = writeFD;
  this->scenegraph = scenegraph;
  this->builder = flatbuffers::FlatBufferBuilder(1024);
}

uint Messenger::generateMessageID() { return pendingMessages.size(); }

void Messenger::sendSignal(const char *object, const char *method,
                           std::vector<uint8_t> &data) {
  sendCall(3, 0, object, method, data);
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

} // namespace StardustXR
