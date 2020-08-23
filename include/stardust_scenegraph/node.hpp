#ifndef STARDUSTXR_NODE_H
#define STARDUSTXR_NODE_H
#define STARDUSTXR_NODE_METHOD(method_name, method_ref) methods.push_back(method_name, std::bind(method_name, this, std::placeholders::_1, std::placeholders::_2));

#include "flatbuffers/flexbuffers.h"
#include <unistd.h>

namespace StardustXR {

typedef std::function<std::vector<uint8_t>(flexbuffers::Reference, bool)> Method;

class Node {
public:
	Node() {}

	std::map<std::string, Method> methods;
	std::map<std::string, Node *> children;
};

} // namespace StardustXR

#endif
