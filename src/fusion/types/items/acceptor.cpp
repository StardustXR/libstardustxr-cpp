#include "acceptor.hpp"
#include "fusion_internal.hpp"

//#include <cctype>

namespace StardustXRFusion {

ItemAcceptor::ItemAcceptor(Spatial *parent, Field &field, Vec3 origin,
                           Quat rotation, std::string itemType)
    : Spatial() {

  core->name = GenerateID();
  core->path = "/item/" + itemType + "/acceptor";

  itemType[0] = std::toupper(itemType[0]);
  std::string createMethod = "create" + itemType + "ItemAcceptor";
  core->methods[core->name] =
      std::bind(&ItemAcceptor::acceptorCallback, this, std::placeholders::_1,
                std::placeholders::_2);
  scenegraph->addNode(core);

  messenger->sendSignal("/item", createMethod,
                        FLEX_ARGS(FLEX_STRING(core->name) FLEX_STRING(
                            parent ? parent->getNodePath() : std::string(""))
                                      FLEX_STRING(field.getNodePath())
                                          FLEX_VEC3(origin) FLEX_QUAT(rotation)
                                              FLEX_STRING(std::string(""))
                                                  FLEX_STRING(core->name)));
}

ItemAcceptor::~ItemAcceptor() {}

} // namespace StardustXRFusion
