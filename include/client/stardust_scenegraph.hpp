#ifndef LIBSTARDUSTXR_CLIENT_STARDUST_SCENEGRAPH_H
#define LIBSTARDUSTXR_CLIENT_STARDUST_SCENEGRAPH_H

#include "scenegraph.hpp"
#include "node.hpp"

namespace StardustXR {

class ClientStardustScenegraph : public ClientScenegraph {
public:
	ClientStardustScenegraph() : ClientScenegraph() {}

	void sendSignal(std::string path, std::string method, flexbuffers::Reference data);
	std::vector<uint8_t> executeMethod(std::string path, std::string method, flexbuffers::Reference args);

	void addNode(std::string path, ClientNode *node);
protected:
	ClientNode root;
	std::vector<uint8_t> executeMethod(std::string path, std::string method, flexbuffers::Reference args, bool returnValue);
	void onPathStep(std::string path, std::function<void(std::string)> pathStepFunction);
};

} // namespace StardustXR

#endif //LIBSTARDUSTXR_CLIENT_STARDUST_SCENEGRAPH_H
