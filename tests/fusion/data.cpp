#include "fusion/fusion.hpp"
#include "fusion/types/fields/spherefield.hpp"
#include "fusion/types/data/receiver.hpp"
#include "fusion/types/data/sender.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();

	Spatial receiverRoot = Spatial::create(nullptr, vec3_forward * 1.0f);
	SphereField receiverField(&receiverRoot, vec3_zero, 0);
	NonSpatialReceiver receiver(&receiverRoot, receiverField);
	receiver.setMask([](flexbuffers::Builder &fbb) {
		fbb.Bool("keyboard", true);
	});

	receiver.onDataReceived = [](std::string senderUUID, flexbuffers::Reference data){
		std::string dataString;
		data.ToString(true, false, dataString);
		data.AsMap()["keymap"].GetType();
		printf("data: %s\n", dataString.c_str());
		exit(0);
	};

	NonSpatialSender sender(nullptr);
	sender.getReceivers([](std::vector<NonSpatialReceiver> &receivers) {
		if(receivers.size() > 0) {
			NonSpatialReceiver recentReceiver = receivers[receivers.size()-1];
			recentReceiver.getMask([](flexbuffers::Reference mask) {
				std::string maskString;
				mask.ToString(true, false, maskString);
				printf("mask: %s\n", maskString.c_str());
			});
			recentReceiver.sendData([](flexbuffers::Builder &fbb) {
				fbb.Bool("keyboard", true);
			});
		}
	});

	StardustXRFusion::StallMainThread();
}
