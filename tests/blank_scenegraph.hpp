#include "scenegraph.hpp"
#include <stdio.h>

namespace StardustXR {

class BlankScenegraph : public Scenegraph {
public:
  explicit BlankScenegraph() : Scenegraph() {}

  void sendSignal(std::string path, std::string method,
                  flexbuffers::Reference data) {
    printf("Sending signal with method %s on object with path %s\n",
           method.c_str(), path.c_str());
    printf("\t");
  }

  std::vector<uint8_t> executeMethod(std::string path, std::string method,
                                     flexbuffers::Reference args) {
    printf("Attempting to execute method %s on object with path %s\n",
           method.c_str(), path.c_str());
    return std::vector<uint8_t>();
  }
};

} // namespace StardustXR
