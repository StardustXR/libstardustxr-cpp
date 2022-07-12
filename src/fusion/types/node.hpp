#pragma once

#include "../common/messenger.hpp"
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/flexbuffers.h>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace StardustXRFusion {

typedef std::function<std::vector<uint8_t>(flexbuffers::Reference, bool)>
    Method;

struct NodeCore {
  NodeCore(std::string nodePath, std::string nodeName, bool indestructible);
  ~NodeCore();

  std::string getPath();

  std::string name = "";
  std::string path = "";
  bool indestructible = false;

  std::map<std::string, Method> methods;
};

class Node {
public:
  Node &operator=(const Node *other) const = delete;
  bool operator==(const Node &other) const;
  bool operator!=(const Node &other) const;
  bool operator<(const Node &other) const;

  const std::string getNodePath() const;
  const std::string getNodeName() const;

  void setEnabled(bool enabled);
  void setBackend(std::shared_ptr<NodeCore> core);
  void sendSignal(std::string signal, StardustXR::ArgsConstructor args);
  void executeMethod(std::string method, StardustXR::ArgsConstructor args,
                     StardustXR::Callback callback);

protected:
  explicit Node();
  explicit Node(const Node &original);

  std::shared_ptr<NodeCore> core;
};

} // namespace StardustXRFusion
