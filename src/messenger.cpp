#include "messenger.hpp"

namespace StardustXR {

Messenger::Messenger(int readFD, int writeFD) {
	this->messageReadFD = readFD;
	this->messageWriteFD = writeFD;
	this->builder = flatbuffers::FlatBufferBuilder(1024);
}

uint Messenger::generateMessageID() { return 0; }

} // namespace StardustXR
