#include "node.hpp"
#include "../fusion_internal.hpp"

namespace StardustXRFusion {


Node::Node(bool destroyable) : destroyable(destroyable) {}
Node::Node(const Node &original) {
	this->nodeName = original.nodeName;
	this->nodePath = original.nodePath;
	this->destroyable = original.destroyable;
}
Node::~Node() {
	if(destroyable) {
		messenger->sendSignal(
			getNodePath().c_str(),
			"destroy",
			FLEX_ARG(FLEX_NULL)
		);
	}
}
bool Node::operator==(const Node &other) const {
	return this->getNodePath() == other.getNodePath();
}
bool Node::operator!=(const Node &other) const {
	return !(*this == other);
}

bool Node::operator<(const Node &other) const {
	return this->getNodePath() < other.getNodePath();
}

const std::string Node::getNodePath() const {
	return nodePath+"/"+nodeName;
}
const std::string Node::getNodeName() const {
	return nodeName;
}

void Node::setEnabled(bool enabled) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setEnabled",
		FLEX_ARG(FLEX_BOOL(enabled))
	);
}

void Node::setBackend(const std::string nodePath, const std::string nodeName) {
	this->nodePath = nodePath;
	this->nodeName = nodeName;
}

} // namespace StardustXRFusion
