#include "scenegraph.hpp"
#include <cstdint>

namespace StardustXRFusion {

FusionScenegraph::FusionScenegraph() {}

void FusionScenegraph::addNode(std::shared_ptr<NodeCore> &node) {
  std::lock_guard<std::mutex> lock(nodesMutex);
  nodes[node->getPath()] = node;
}

void FusionScenegraph::removeNode(NodeCore &node) {
  std::lock_guard<std::mutex> lock(nodesMutex);
  auto nodeRef = nodes.find(node.getPath());
  if (nodeRef != nodes.end())
    nodes.erase(nodeRef);
}

std::vector<uint8_t> FusionScenegraph::sendCall(std::string nodePath,
                                                std::string methodName,
                                                flexbuffers::Reference data,
												bool method) {
	std::unique_lock<std::mutex> lock(nodesMutex);
  auto node = nodes[nodePath].lock();
  if (node) {
    auto methodRef = node->methods.find(methodName);
    if (methodRef != node->methods.end()) {
		lock.unlock();
      return methodRef->second(data, method);
    } else {
      fprintf(stderr, "Method/signal \"%s\" does not exist\n",
              methodName.c_str());
    }
  } else {
    fprintf(stderr, "Node \"%s\" does not exist\n", nodePath.c_str());
  }
  return std::vector<uint8_t>();
}

void FusionScenegraph::sendSignal(std::string nodePath, std::string methodName,
                                  flexbuffers::Reference data) {
  sendCall(nodePath, methodName, data, false);
}
std::vector<uint8_t>
FusionScenegraph::executeMethod(std::string nodePath, std::string methodName,
                                flexbuffers::Reference data) {
  return sendCall(nodePath, methodName, data, true);
}

} // namespace StardustXRFusion
