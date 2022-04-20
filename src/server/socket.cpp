#include "socket.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>

const uint32_t MAX_INSTANCE_COUNT = 32;

namespace StardustXRServer {

SocketHandler::SocketHandler(bool &successful) :
socketPath(lockSocketPath()){
	this->successful = socketPath != "" && createSocket();
	successful = this->successful;
}

SocketHandler::~SocketHandler() {
	if(successful) close();
}

std::string SocketHandler::lockSocketPath() {
	std::string socketPath = getenv("XDG_RUNTIME_DIR");
	socketPath += "/stardust-";
	uint32_t instanceNumber = 0;
	std::string instanceNumberString = "0";
	do {
		instanceNumberString = std::to_string(instanceNumber);
		std::string lockPath = socketPath+instanceNumberString+".lock";
		int socketLockFD = open(lockPath.c_str(), O_CREAT | O_CLOEXEC | O_RDWR, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP));
		if(socketLockFD < 0) continue;
		if(flock(socketLockFD, LOCK_EX | LOCK_NB) < 0) continue;
		break;
	} while (instanceNumber++ < MAX_INSTANCE_COUNT);

	socketPath += instanceNumberString;
	setenv("STARDUST_INSTANCE", instanceNumberString.c_str(), true);
	return ++instanceNumber < MAX_INSTANCE_COUNT ? socketPath : "";
}

bool SocketHandler::createSocket() {
	printf("Trying to make a socket at %s.\n", socketPath.c_str());
	if ((socketFD = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1) return false;

	sockaddr_un local = { .sun_family = AF_UNIX, };
	unlink(socketPath.c_str());
	socketPath.copy(local.sun_path, sizeof(local.sun_path));

	if(fcntl(socketFD, F_GETFL) & O_NONBLOCK) return false;

//	int len = strlen(local.sun_path) + sizeof(local.sun_family);
	int len = sizeof(sockaddr_un);
	if (bind(socketFD, (sockaddr *)&local, len) == -1) return false;
	if (listen(socketFD, 5) == -1) return false;
	return true;
}

int SocketHandler::acceptNewClient() {
	return accept(socketFD, NULL, NULL);
}

int SocketHandler::fd() {
	return socketFD;
}

void SocketHandler::close() {
	shutdown(socketFD, SHUT_RDWR);
	::close(socketFD);
	successful = false;
}

} // namespace StardustXR
