#include "receiver.hpp"
#include "sender.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"



namespace StardustXRFusion {

PulseReceiver::PulseReceiver(Spatial *parent, Field &field, Vec3 origin, Quat rotation) : Spatial(true) {
	nodePath = "/data/receiver";
	nodeName = GenerateID();

	scenegraph->addMethod(nodeName, std::bind(&PulseReceiver::dataReceived, this, std::placeholders::_1, std::placeholders::_2));
	messenger->sendSignal(
		"/data",
		"createPulseReceiver",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(field.getNodePath())
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
}
PulseReceiver::PulseReceiver(PulseSender *sender, std::string nodePath, std::string nodeName) : Spatial(false) {
	this->sender = sender;
	this->nodePath = nodePath;
	this->nodeName = nodeName;
}

void PulseReceiver::getMask(std::function<void (flexbuffers::Reference)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"getMask",
		FLEX_ARG(
			FLEX_NULL
		), [callback](flexbuffers::Reference data) {
			callback(data);
		}
	);
}
void PulseReceiver::getMask(std::function<void (flexbuffers::Map mask)> callback) {
	getMask([callback](flexbuffers::Reference mask) {
		callback(mask.AsMap());
	});
}

void PulseReceiver::setMask(std::vector<uint8_t> mask) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setMask",
		FLEX_ARG(
			FLEX_BLOB(mask)
		)
	);
}
void PulseReceiver::setMask(std::function<void (flexbuffers::Builder &)> argsConstructor) {
	flexbuffers::Builder fbb(1024);
	fbb.Map([&]() {
		argsConstructor(fbb);
	});
	fbb.Finish();
	setMask(fbb.GetBuffer());
}

void PulseReceiver::sendData(std::vector<uint8_t> data) {
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
void PulseReceiver::sendData(std::function<void (flexbuffers::Builder &)> dataConstructor) {
	flexbuffers::Builder fbb(1024);
	fbb.Map([&]() {
		dataConstructor(fbb);
	});
	fbb.Finish();
	sendData(fbb.GetBuffer());
}

std::vector<uint8_t> PulseReceiver::dataReceived(flexbuffers::Reference data, bool) {
	flexbuffers::Vector vector = data.AsVector();
	std::string senderUUID = vector[0].AsString().str();
	flexbuffers::Blob sentDataBlob = vector[1].AsBlob();

	onDataReceived(senderUUID, flexbuffers::GetRoot(sentDataBlob.data(), sentDataBlob.size()));

	return std::vector<uint8_t>();
}

} // namespace StardustXRFusion
