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

int ConnectClient() {
	setenv("STARDUST_INSTANCE", "0", false);
	std::string socketPath = getenv("XDG_RUNTIME_DIR");
	socketPath += "/stardust-";
	socketPath += getenv("STARDUST_INSTANCE");
	int fd, len;

	if ((fd = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1)
		return 0;

	printf("Trying to connect to Stardust's server at %s...\n", socketPath.c_str());

	struct sockaddr_un server = {};
	server.sun_family = AF_UNIX;
	socketPath.copy(server.sun_path, sizeof(server.sun_path));

	len = strlen(server.sun_path) + sizeof(server.sun_family);
	if (connect(fd, (struct sockaddr *)&server, len) == -1)
		return 0;

	printf("Connected.\n");
	return fd;
}

} // namespace StardustXR
