#pragma once
#define STARDUSTXR_NODE_METHOD(method_name, method_ref) methods[method_name] = std::bind(method_ref, this, std::placeholders::_1, std::placeholders::_2);

#include "flatbuffers/flexbuffers.h"
#include <functional>

namespace StardustXR {

typedef std::function<std::vector<uint8_t>(flexbuffers::Reference, bool)> NodeMethod;

class Node {
public:
	Node() {}
	~Node() {
		for(const auto &node : children)
			delete node.second;
	}

	std::map<std::string, NodeMethod> methods;
	std::map<std::string, Node *> children;
};

} // namespace StardustXR
