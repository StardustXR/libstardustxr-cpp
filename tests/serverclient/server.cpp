#include "server/messengermanager.hpp"
#include "server/stardust_scenegraph.hpp"

class TestNode : public StardustXR::ServerNode {
public:
	explicit TestNode() {
		STARDUSTXR_NODE_METHOD("echo", &TestNode::echo)
	}

	std::vector<uint8_t> echo(int sessionID, flexbuffers::Reference stringVariant, bool returnValue) {
		const char *string = stringVariant.AsString().c_str();
		printf("Echoing back \"%s\" on client with sessionID of %i\n", string, sessionID);
		if(returnValue) {
			flexbuffers::Builder fbb;
			fbb.String(string);
			fbb.Finish();
			return fbb.GetBuffer();
		}
		return std::vector<uint8_t>();
	}
};

int main(int argc, char *argv[]) {
	printf("Server starting...\n");

	StardustXR::ServerStardustScenegraph scenegraph;
	scenegraph.addNode("/test", new TestNode());

	StardustXR::MessengerManager messengerManager(&scenegraph);

	std::this_thread::sleep_for(std::chrono::seconds(300));
	return 0;
}
