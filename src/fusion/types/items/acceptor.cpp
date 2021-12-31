#include "acceptor.hpp"
#include "fusion_internal.hpp"

namespace StardustXRFusion {

ItemAcceptor::ItemAcceptor(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation, std::string createMethod) :
	Spatial(parent, origin, orientation) {
	destroyable = true;

	nodeName = GenerateID();
	nodePath = "/item/acceptor";

	scenegraph->addMethod(nodeName, std::bind(&ItemAcceptor::acceptorCallback, this, std::placeholders::_1, std::placeholders::_2));
	messenger->sendSignal(
		"/item",
		createMethod.c_str(),
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_STRING(field.getNodePath())
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
}

} // namespace StardustXRFusion
