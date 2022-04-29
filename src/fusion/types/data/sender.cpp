#include "sender.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"
#include <flatbuffers/flexbuffers.h>



namespace StardustXRFusion {

PulseSender::PulseSender(Spatial *parent, Vec3 origin, Quat rotation) : Spatial(true) {
	nodePath = "/data/sender";
	nodeName = GenerateID();

	messenger->sendSignal(
		"/data",
		"createPulseSender",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_STRING(std::string(""))
			FLEX_STRING(nodeName)
		)
	);
}

void PulseSender::getReceivers(std::function<void (std::vector<PulseReceiver> &)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"getReceivers",
		FLEX_ARG(
			FLEX_NULL
		), [this, callback](flexbuffers::Reference data) {
			flexbuffers::Vector flexReceivers = data.AsVector();
			std::vector<PulseReceiver> receivers;
			for(size_t i=0; i<flexReceivers.size(); ++i) {
				receivers.emplace_back(this, getNodePath(), flexReceivers[i].AsString().str());
			}
			callback(receivers);
		}
	);
}

} // namespace StardustXRFusion
