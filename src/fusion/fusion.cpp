#include "fusion.hpp"
#include "../client/connector.hpp"

namespace StardustXRFusion {

StardustXRFusion::FusionScenegraph *scenegraph = nullptr;
StardustXR::ClientMessenger *messenger = nullptr;

LifeCycleInterface *lifeCycle = nullptr;

std::string GenerateID() {
	char id[32];
	sprintf(id, "%ld", time(nullptr));
	return std::string(id);
}

bool Setup() {
	printf("Client starting...\n");
	int readFD, writeFD;
	if (!StardustXR::ConnectClient("/tmp/stardust.sock", readFD, writeFD)) {
		perror("Client failed to connect to server");
		return false;
	}

	scenegraph = new FusionScenegraph();
	messenger = new StardustXR::ClientMessenger(readFD, writeFD, scenegraph);
	messenger->startHandler();

	return true;
}

LifeCycleInterface *LifeCycle() {
	if(!lifeCycle)
		lifeCycle = new LifeCycleInterface();
	return lifeCycle;
}

}
