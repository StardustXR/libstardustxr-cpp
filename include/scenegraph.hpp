#include <unistd.h>

namespace StardustXR {

class Scenegraph {
  Scenegraph(){};
  virtual ~Scenegraph(){};

  virtual void executeMethod(std::string path, std::string method) = 0;
};

} // namespace StardustXR
