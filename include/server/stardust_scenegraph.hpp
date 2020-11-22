#ifndef LIBSTARDUSTXR_SERVER_STARDUST_SCENEGRAPH_H
#define LIBSTARDUSTXR_SERVER_STARDUST_SCENEGRAPH_H

#include "scenegraph.hpp"
#include "node.hpp"

namespace StardustXR {

class ServerStardustScenegraph : public ServerScenegraph {
public:
	ServerStardustScenegraph() : ServerScenegraph() {}

	void sendSignal(int sessionID, std::string path, std::string method, flexbuffers::Reference data);
	std::vector<uint8_t> executeMethod(int sessionID, std::string path, std::string method, flexbuffers::Reference args);

	void addNode(std::string path, ServerNode *node);
	ServerNode root;
protected:
	std::vector<uint8_t> executeMethod(int sessionID, std::string path, std::string method, flexbuffers::Reference args, bool returnValue);
	void onPathStep(std::string path, std::function<void(std::string)> pathStepFunction);
};

} // namespace StardustXR

#endif //LIBSTARDUSTXR_SERVER_STARDUST_SCENEGRAPH_H
