#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <sys/wait.h>

#include <iostream>
#include <time.h>
#include <unistd.h>

namespace StardustXR {

void SendFD(int socket, int fd);

bool ConnectClient(std::string path, int &read, int &write);

} // namespace StardustXR
