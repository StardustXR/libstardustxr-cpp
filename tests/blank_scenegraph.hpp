#include "scenegraph.hpp"
#include <stdio.h>

namespace StardustXR {

class BlankScenegraph : public Scenegraph {
public:
  explicit BlankScenegraph() : Scenegraph() {}

  void executeMethod(std::string path, std::string method,
                     flexbuffers::Reference args) {
    printf("Attempting to execute method %s on object with path %s",
           method.c_str(), path.c_str());
  }
};

} // namespace StardustXR
