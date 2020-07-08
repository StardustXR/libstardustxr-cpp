#ifndef STARDUSTXR_SCENEGRAPH_H
#define STARDUSTXR_SCENEGRAPH_H

#include <unistd.h>

namespace StardustXR {

class Scenegraph {
  Scenegraph(){};
  virtual ~Scenegraph(){};

  virtual void executeMethod(std::string path, std::string method) = 0;
};

} // namespace StardustXR

#endif // STARDUSTXR_SCENEGRAPH_H
