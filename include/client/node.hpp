#ifndef STARDUSTXR_CLIENT_NODE_H
#define STARDUSTXR_CLIENT_NODE_H
#define STARDUSTXR_NODE_METHOD(method_name, method_ref) methods[method_name] = std::bind(method_ref, this, std::placeholders::_1, std::placeholders::_2);

#include "flatbuffers/flexbuffers.h"
#include <unistd.h>

namespace StardustXR {

typedef std::function<std::vector<uint8_t>(flexbuffers::Reference, bool)> ClientMethod;

class ClientNode {
public:
	ClientNode() {}
	~ClientNode() {
		for(const auto &node : children)
			delete node.second;
	}

	std::map<std::string, ClientMethod> methods;
	std::map<std::string, ClientNode *> children;
};

} // namespace StardustXR

#endif //STARDUSTXR_CLIENT_NODE_H
