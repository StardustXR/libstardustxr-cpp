#ifndef LIBSTARDUSTXR_SERVER_NODE_H
#define LIBSTARDUSTXR_SERVER_NODE_H
#define STARDUSTXR_NODE_METHOD(method_name, method_ref) methods[method_name] = std::bind(method_ref, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

#include "flatbuffers/flexbuffers.h"
#include <functional>

namespace StardustXR {

typedef std::function<std::vector<uint8_t>(uint, flexbuffers::Reference, bool)> ServerMethod;

class ServerNode {
public:
	ServerNode() {}
	virtual ~ServerNode() {
		for(const auto &node : children)
			delete node.second;
	}

	std::map<std::string, ServerMethod> methods;
	std::map<std::string, ServerNode *> children;
};

} // namespace StardustXR

#endif //LIBSTARDUSTXR_SERVER_NODE_H
