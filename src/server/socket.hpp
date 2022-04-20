#pragma once

#include <fcntl.h>
#include <list>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <thread>

#include <iostream>
#include <time.h>
#include <unistd.h>

namespace StardustXRServer {

class SocketHandler {
public:
	SocketHandler(bool &successful);
	~SocketHandler();

	const std::string socketPath;
	int acceptNewClient();
	int fd();
	void close();
protected:
	static std::string lockSocketPath();
	bool createSocket();
	int socketFD;
private:
	typedef struct {
		int fd;
		char buf[256];
	} RecieveFDReturn;
	bool successful;
};

} // namespace StardustXR
