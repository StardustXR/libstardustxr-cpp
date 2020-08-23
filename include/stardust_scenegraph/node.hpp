#ifndef STARDUSTXR_NODE_H
#define STARDUSTXR_NODE_H

#include "flatbuffers/flexbuffers.h"
#include <unistd.h>

namespace StardustXR {

class Node;	
typedef std::vector<uint8_t> (Node::*Method)(flexbuffers::Reference ref, bool returnValue);

class Node {
public:
	Node() {}

	std::map<std::string, Method> methods;
	std::map<std::string, Node *> children;
};

} // namespace StardustXR

#endif
