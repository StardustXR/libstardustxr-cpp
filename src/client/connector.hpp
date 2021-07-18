#pragma once

#include <string>

namespace StardustXR {

void SendFD(int socket, int fd);

bool ConnectClient(std::string path, int &read, int &write);

} // namespace StardustXR
