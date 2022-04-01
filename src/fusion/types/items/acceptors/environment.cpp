#include "environment.hpp"
#include "fusion_internal.hpp"

namespace StardustXRFusion {

EnvironmentItemAcceptor::EnvironmentItemAcceptor(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation) :
	ItemAcceptor(parent, field, origin, orientation, "environment") {}

std::vector<uint8_t> EnvironmentItemAcceptor::acceptorCallback(flexbuffers::Reference data, bool) {
	flexbuffers::Vector flexVec = data.AsVector();
	bool captured = flexVec[0].AsBool();
	std::string nodeName = flexVec[1].AsString().str();
	flexbuffers::Vector dataVec = flexVec[2].AsVector();

	EnvironmentItem item("/item/panel", nodeName);
	if(captured)
		itemCapturedMethod(item, EnvironmentItem::Data {dataVec[0].AsString().str()});
	else
		itemReleasedMethod(item);
	return std::vector<uint8_t>();
}

}
