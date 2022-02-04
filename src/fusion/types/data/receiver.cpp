#include "receiver.hpp"
#include "sender.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"

using namespace SKMath;

namespace StardustXRFusion {

NonSpatialReceiver::NonSpatialReceiver(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation) : Spatial(parent, origin, orientation, vec3_one) {
	nodePath = "/data/receiver/";
	nodeName = GenerateID();

	scenegraph->addMethod(nodeName, std::bind(&NonSpatialReceiver::dataReceived, this, std::placeholders::_1, std::placeholders::_2));
	messenger->sendSignal(
		"/data",
		"createNonSpatialReceiver",
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
NonSpatialReceiver::NonSpatialReceiver(NonSpatialSender *sender, std::string nodePath, std::string nodeName) : Spatial(nullptr, nodePath, nodeName) {
	this->destroyable = false;
	this->sender = sender;
	this->nodePath = nodePath;
	this->nodeName = nodeName;
}

void NonSpatialReceiver::sendData(std::vector<uint8_t> data) {
	messenger->sendSignal(
		sender->getNodePath().c_str(),
		"sendData",
		[&](flexbuffers::Builder &fbb) {
			fbb.Vector([&]() {
				fbb.String(getNodeName());
				fbb.Blob(data.data(), data.size());
			});
		}
	);
}

std::vector<uint8_t> NonSpatialReceiver::dataReceived(flexbuffers::Reference data, bool) {
	flexbuffers::Vector vector = data.AsVector();
	std::string senderUUID = vector[0].AsString().str();
	flexbuffers::Blob sentDataBlob = vector[1].AsBlob();

	onDataReceived(senderUUID, flexbuffers::GetRoot(sentDataBlob.data(), sentDataBlob.size()));

	return std::vector<uint8_t>();
}

} // namespace StardustXRFusion
