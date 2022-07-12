#include "node.hpp"
#include "../fusion_internal.hpp"

namespace StardustXRFusion {

NodeCore::NodeCore(std::string path, std::string name, bool indestructible)
    : path(path), name(name), indestructible(indestructible) {}

NodeCore::~NodeCore() {
  if (!indestructible) {
    if (messenger) {
      messenger->sendSignal(getPath(), "destroy", FLEX_ARG(FLEX_NULL));
    }
    if (scenegraph) {
      scenegraph->removeNode(*this);
    }
  }
}

std::string NodeCore::getPath() { return path + "/" + name; }

Node::Node() {
  this->core = std::shared_ptr<NodeCore>(new NodeCore("", "", false));
}
Node::Node(const Node &original) { this->core = original.core; }

bool Node::operator==(const Node &other) const {
  return this->getNodePath() == other.getNodePath();
}
bool Node::operator!=(const Node &other) const { return !(*this == other); }

bool Node::operator<(const Node &other) const {
  return this->getNodePath() < other.getNodePath();
}

const std::string Node::getNodePath() const { return core->getPath(); }
const std::string Node::getNodeName() const { return core->name; }

void Node::setEnabled(bool enabled) {
  sendSignal("setEnabled", FLEX_ARG(FLEX_BOOL(enabled)));
}

void Node::setBackend(std::shared_ptr<NodeCore> core) { this->core = core; }

void Node::sendSignal(std::string signal, StardustXR::ArgsConstructor args) {
  messenger->sendSignal(getNodePath(), signal, args);
}
void Node::executeMethod(std::string signal, StardustXR::ArgsConstructor args,
                         StardustXR::Callback callback) {
  executeMethod(signal, args, callback);
}

} // namespace StardustXRFusion
