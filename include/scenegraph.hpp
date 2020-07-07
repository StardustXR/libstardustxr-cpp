#include <unistd.h>

namespace StardustXR {

class Scenegraph {
  Scenegraph();

  pure virtual void executeMethod(std::string path, std::string method);
}

} // namespace StardustXR
