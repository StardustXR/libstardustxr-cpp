#pragma once

#include "../../values.hpp"
#include "../fields/field.hpp"
#include "../spatial/spatial.hpp"
#include "datamap.hpp"

#include <map>

namespace flexbuffers {
class Reference;
}

namespace StardustXRFusion {

class HandInput;
class PointerInput;

class InputHandler : public Spatial {
public:
  explicit InputHandler(Spatial *parent, Field &field, Vec3 origin,
                        Quat rotation);
  explicit InputHandler(Spatial *parent, Vec3 origin, Quat rotation);

  void setField(Field *field);

  std::function<bool(const std::string uuid, const PointerInput &,
                     const Datamap &)>
      pointerHandlerMethod = [](const std::string uuid, const PointerInput &,
                                const Datamap &) { return false; };
  std::function<bool(const std::string uuid, const HandInput &,
                     const Datamap &)>
      handHandlerMethod = [](const std::string uuid, const HandInput &,
                             const Datamap &) { return false; };

private:
  std::vector<uint8_t> inputEvent(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
