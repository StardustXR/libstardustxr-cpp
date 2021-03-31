#include "fusion.hpp"
#include "libstardustxr.hpp"
#include <stardustxr/client/connector.hpp>
#include <stardustxr/client/messenger.hpp>

extern bool StardustXRFusion::Setup() {
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
