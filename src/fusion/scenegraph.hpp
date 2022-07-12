#pragma once

#include "../common/scenegraph.hpp"
#include "types/node.hpp"
#include <functional>
#include <map>
#include <memory>
#include <mutex>

namespace StardustXRFusion {

class FusionScenegraph : public StardustXR::Scenegraph {
public:
  explicit FusionScenegraph();

  void addNode(std::shared_ptr<NodeCore> &node);
  void removeNode(NodeCore &node);

  void sendSignal(std::string nodePath, std::string methodName,
                  flexbuffers::Reference data);
  std::vector<uint8_t> executeMethod(std::string nodePath,
                                     std::string methodName,
                                     flexbuffers::Reference data);

protected:
  std::vector<uint8_t> sendCall(std::string nodePath, std::string methodName,
                                flexbuffers::Reference data, bool method);
  std::mutex nodesMutex;
  std::map<std::string, std::weak_ptr<NodeCore>> nodes;
};

} // namespace StardustXRFusion
