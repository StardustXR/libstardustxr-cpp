#include "dummy/blank_scenegraph.hpp"
#include "client/clientconnector.hpp"
#include "client/client_messenger.hpp"

int main(int argc, char *argv[]) {
	printf("Client starting...\n");
	int readFD, writeFD;
	if (!StardustXR::ConnectClient("/tmp/stardust.sock", readFD, writeFD)) {
		perror("Client failed to connect to server");
		return 1;
	}

	StardustXR::BlankScenegraph scenegraph;
	StardustXR::ClientMessenger messenger(readFD, writeFD, &scenegraph);

	flexbuffers::Builder fbb;
	fbb.String("Hello Universe!");
	fbb.Finish();
	std::vector<uint8_t> data = fbb.GetBuffer();

	const char *echo = messenger.executeRemoteMethod("/test", "echo", data).AsString().c_str();

	printf("Got back echo \"%s\"\n", echo);

	std::this_thread::sleep_for(std::chrono::seconds(300));

	return 0;
}
