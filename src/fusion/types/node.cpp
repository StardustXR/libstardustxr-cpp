#include "node.hpp"

namespace StardustXRFusion {

Node::Node() {}
Node::~Node() {}

std::string Node::getNodePath() {
	return nodePath+"/"+nodeName;
}

} // namespace StardustXRFusion
