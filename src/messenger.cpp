#include "messenger.hpp"

namespace StardustXR {

Messenger::Messenger(int readFD, int writeFD, Scenegraph *scenegraph) {
  this->messageReadFD = readFD;
  this->messageWriteFD = writeFD;
  this->scenegraph = scenegraph;
  this->builder = flatbuffers::FlatBufferBuilder(1024);
}

uint Messenger::generateMessageID() { return pendingMessages.size(); }

void Messenger::sendMessage(uint8_t *buffer, uint size) {
  write(messageWriteFD, &size, 4);
  write(messageWriteFD, buffer, size);
}

} // namespace StardustXR
