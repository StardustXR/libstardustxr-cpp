#include "zone.hpp"

#include "../flex.hpp"
#include "../fusion_internal.hpp"
#include <flatbuffers/flexbuffers.h>

using namespace SKMath;

namespace StardustXRFusion {

Zone::Zone(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation) : Spatial(parent, origin, orientation, vec3_one) {
	nodePath = "/spatial/zone";
	nodeName = GenerateID();

	scenegraph->addMethod(nodeName, std::bind(&Zone::updateZone, this, std::placeholders::_1, std::placeholders::_2));
	messenger->sendSignal(
		"/spatial",
		"createZone",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(field.getNodePath())
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
}
Zone::~Zone() {
	scenegraph->removeMethod(nodeName);
	for(auto space : spatials) {
		release(space.second);
	}
}

void Zone::isCaptured(Spatial &spatial, std::function<void(bool)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"isCaptured",
		FLEX_ARG(
			FLEX_STRING(spatial.getNodeName())
		),
		[callback](flexbuffers::Reference data) {
			callback(data.AsBool());
		}
	);
}

void Zone::capture(Spatial &spatial) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"capture",
		FLEX_ARG(
			FLEX_STRING(spatial.getNodeName())
		)
	);
}

void Zone::release(Spatial &spatial) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"release",
		FLEX_ARG(
			FLEX_STRING(spatial.getNodeName())
		)
	);
}

std::vector<uint8_t> Zone::updateZone(flexbuffers::Reference data, bool) {
	flexbuffers::Vector vector = data.AsVector();
	flexbuffers::TypedVector enter = vector[0].AsTypedVector();
	flexbuffers::TypedVector exit  = vector[1].AsTypedVector();

	for(uint i=0; i<enter.size(); ++i) {
		std::string uuid = enter[i].AsString().str();
		spatials.emplace(uuid, Spatial{nullptr, getNodePath(), uuid});
		onSpatialEnter(spatials.at(uuid));
	}
	for(uint i=0; i<exit.size(); ++i) {
		std::string uuid = exit[i].AsString().str();
		spatials.erase(uuid);
		onSpatialLeave(uuid);
	}
	return std::vector<uint8_t>();
}

} // namespace StardustXRFusion
