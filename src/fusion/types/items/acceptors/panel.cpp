#include "panel.hpp"
#include "fusion_internal.hpp"

namespace StardustXRFusion {

PanelItemAcceptor::PanelItemAcceptor(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation) :
	ItemAcceptor(parent, field, origin, orientation, "panel") {}

std::vector<uint8_t> PanelItemAcceptor::acceptorCallback(flexbuffers::Reference data, bool) {
	flexbuffers::Vector flexVec = data.AsVector();
	bool captured = flexVec[0].AsBool();
	std::string nodeName = flexVec[1].AsString().str();
	flexbuffers::Vector dataVec = flexVec[2].AsVector();

	PanelItem item(getNodePath(), nodeName);
	if(captured)
		itemCapturedMethod(item, PanelItem::Data {dataVec[0].AsUInt32(), dataVec[1].AsUInt32()});
	else
		itemReleasedMethod(item);
	return std::vector<uint8_t>();
}

}

