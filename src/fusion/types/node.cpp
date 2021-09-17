#include "node.hpp"
#include "../fusion_internal.hpp"

namespace StardustXRFusion {

Node::Node() {}
Node::~Node() {
	messenger->sendSignal(
		getNodePath().c_str(),
		"destroy",
		FLEX_ARG(FLEX_NULL)
	);
}

std::string Node::getNodePath() {
	return nodePath+"/"+nodeName;
}

} // namespace StardustXRFusion
