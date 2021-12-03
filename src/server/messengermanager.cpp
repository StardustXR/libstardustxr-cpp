#include "messengermanager.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>

const uint32_t MAX_INSTANCE_COUNT = 32;

namespace StardustXR {

MessengerManager::MessengerManager() {
	this->socketPath = std::string(getenv("XDG_RUNTIME_DIR"));
	this->socketPath += "/stardust-";
	uint32_t instanceNumber = 0;
	std::string instanceNumberString = "0";
	do {
		instanceNumberString = std::to_string(instanceNumber);
		std::string lockPath = socketPath+instanceNumberString+".lock";
		socketLockFD = open(lockPath.c_str(), O_CREAT | O_CLOEXEC | O_RDWR, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP));
		if(socketLockFD < 0)
			continue;
		if(flock(socketLockFD, LOCK_EX | LOCK_NB) < 0)
			continue;
		break;
	} while (instanceNumber++ < MAX_INSTANCE_COUNT);

	this->socketPath += instanceNumberString;
	setenv("STARDUST_INSTANCE", instanceNumberString.c_str(), true);

	this->socketThread = std::thread(&StardustXR::MessengerManager::socketLoop, this);
}
MessengerManager::~MessengerManager() {}

void MessengerManager::socketLoop() {
	printf("socketLoop: loop starting, trying to make a socket at %s .\n", socketPath.c_str());
	int s;
	struct sockaddr_un local;
	if ((s = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1) {
		perror("socket");
		exit(1);
	};

	local.sun_family = AF_UNIX; /* local is declared before socket() ^ */
	socketPath.copy(local.sun_path, sizeof(local.sun_path));
	unlink(local.sun_path);
	int len1 = strlen(local.sun_path) + sizeof(local.sun_family);

	if (bind(s, (struct sockaddr *)&local, len1) == -1) {
		perror("bind");
		exit(1);
	}
	if (listen(s, 5) == -1) {
		perror("listen");
		exit(1);
	}
	unsigned int len = sizeof(struct sockaddr_un);
	while (1) {
		int connectionFD;
		sockaddr_un connectionSocket;
		printf("socketLoop: waiting for a connection...\n");
		if ((connectionFD = accept(s, (sockaddr *)&connectionSocket, &len)) == -1) {
			perror("accept");
			exit(1);
		}
		printf("socketLoop: client connected on %s\n", socketPath.c_str());
		clientConnected(connectionFD);
	}
}

} // namespace StardustXR
