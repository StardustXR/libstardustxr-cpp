#include "fusion/fusion.hpp"
#include "fusion/types/fields/spherefield.hpp"
#include "fusion/types/data/receiver.hpp"
#include "fusion/types/data/sender.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

int main(int, char *[]) {
	StardustXRFusion::Setup();

	flexbuffers::Builder fbb(1024);
	fbb.Map([&]() {
		fbb.String("type", "keyboard");
	});
	fbb.Finish();

	Spatial receiverRoot = Spatial::create(nullptr, vec3_forward * 1.0f);
	SphereField receiverField(&receiverRoot, vec3_zero, 0);
	NonSpatialReceiver receiver(&receiverRoot, receiverField);
	receiver.setMask(fbb.GetBuffer());

	receiver.onDataReceived = [](std::string senderUUID, flexbuffers::Reference data){
		std::string dataString;
		data.ToString(true, false, dataString);
		printf("data: %s\n", dataString.c_str());
		exit(0);
	};

	NonSpatialSender sender(nullptr);
	sender.getReceivers([](std::vector<NonSpatialReceiver> &receivers) {
		if(receivers.size() > 0) {
			flexbuffers::Builder fbb(1024);
			fbb.Map([&]() {
				fbb.String("type", "voiceCommand");
				fbb.String("voiceCommand", "follow player");
			});
			fbb.Finish();

			NonSpatialReceiver recentReceiver = receivers[receivers.size()-1];
			recentReceiver.getMask([](flexbuffers::Map mask) {
				printf("mask: %s\n", mask.Values()[0].ToString().c_str());
			});
			recentReceiver.sendData(fbb.GetBuffer());
		}
	});

	StardustXRFusion::StallMainThread();
}
