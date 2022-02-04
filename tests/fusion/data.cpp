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

	receiver.onDataReceived = [](std::string senderUUID, flexbuffers::Reference data){
		std::string dataString;
		data.ToString(true, false, dataString);
		printf("%s", dataString.c_str());

//		flexbuffers::Map datamap = data.AsMap();
//		for(size_t k=0; k<datamap.size(); ++k) {
//			printf("%s : %s", datamap.Keys()[k].AsKey(), datamap.Values()[k].ToString().c_str());
//		}
	};

	NonSpatialSender sender(nullptr);
	sender.getReceivers([](std::vector<NonSpatialReceiver> &receivers) {
		flexbuffers::Builder fbb(1024);
		fbb.Map([&]() {
			fbb.Bool("test", true);
		});
		fbb.Finish();
		if(receivers.size() > 0)
			receivers[receivers.size()-1].sendData(fbb.GetBuffer());
	});

	StardustXRFusion::StallMainThread();
}
