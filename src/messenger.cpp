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
                           std::vector<uint8_t> &argumentsFlexBuffer) {

  builder.Clear();

  auto object_path = builder.CreateString(object);
  auto method_name = builder.CreateString(method);

  MessageBuilder messageBuilder(builder);
  messageBuilder.add_type(3);
  messageBuilder.add_id(generateMessageID());
  messageBuilder.add_object(object_path);
  messageBuilder.add_method(method_name);
  messageBuilder.add_data(argumentsFlexBuffer);
  auto message = messageBuilder.Finish();

  builder.Finish(message);
  sendMessage(builder.GetBufferPointer(), builder.GetSize());
}

void Messenger::sendMessage(uint8_t *buffer, uint size) {
  write(messageWriteFD, &size, 4);
  write(messageWriteFD, buffer, size);
}

} // namespace StardustXR
