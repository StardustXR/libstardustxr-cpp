#pragma once

#include <string>

namespace StardustXR {

void SendFD(int socket, int fd);

bool ConnectClient(int &read, int &write);

} // namespace StardustXR
