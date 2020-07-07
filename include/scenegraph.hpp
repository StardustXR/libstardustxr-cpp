#include <unistd.h>

namespace StardustXR {

class Scenegraph {
  Scenegraph();

  pure virtual void signal(std::string path, std::string method);
}

} // namespace StardustXR
