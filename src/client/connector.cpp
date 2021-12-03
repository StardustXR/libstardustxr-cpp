#include "connector.hpp"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <sys/wait.h>

#include <iostream>
#include <time.h>
#include <unistd.h>

namespace StardustXR {

bool ConnectClient(int &readFD, int &writeFD) {
	setenv("STARDUST_INSTANCE", "0", false);
	std::string socketPath = getenv("XDG_RUNTIME_DIR");
	socketPath += "/stardust-";
	socketPath += getenv("STARDUST_INSTANCE");
	int s, len;

	if ((s = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1) {
		perror("socket");
		return false;
	}

	printf("Trying to connect to Stardust's server at %s...\n", socketPath.c_str());

	struct sockaddr_un server = {};
	server.sun_family = AF_UNIX;
	socketPath.copy(server.sun_path, sizeof(server.sun_path));

	len = strlen(server.sun_path) + sizeof(server.sun_family);
	if (connect(s, (struct sockaddr *)&server, len) == -1) {
		perror("connect");
		return false;
	}

	printf("Connected.\n");

	readFD = s;
	writeFD = s;

	pid_t pid = getpid();

	write(writeFD, &pid, sizeof(pid_t));
	return true;
}

} // namespace StardustXR
