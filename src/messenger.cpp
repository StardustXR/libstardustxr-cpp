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

uint Messenger::generateMessageID() { return 0; }

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

void Messenger::sendMessage(uint8_t *buffer, uint32_t size) {
  write(messageWriteFD, &size, 4);
  write(messageWriteFD, buffer, size);
}

void Messenger::messageHandler() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
    delete message;
  }
}

void Messenger::handleMessage(const Message *message) {
  switch (message->type()) {
  case 0:
    fputs(message->error()->c_str(), stderr);
    break;
  case 1:
  case 2:
    scenegraph->executeMethod(message->object()->str(),
                              message->method()->str(),
                              message->data_flexbuffer_root());
    break;
  }
}

} // namespace StardustXR
