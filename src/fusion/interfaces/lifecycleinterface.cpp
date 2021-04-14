#include "lifecycleinterface.hpp"

#include "../flex.hpp"
#include "../fusion.hpp"

namespace StardustXRFusion {

LifeCycleInterface::LifeCycleInterface() {
//	FUSION_SCENEGRAPH_METHOD("logicStep", &LifeCycleInterface::logicStep)
	scenegraph->methods["logicStep"] = std::bind(&LifeCycleInterface::logicStep, this, std::placeholders::_1, std::placeholders::_2);

	messenger->sendSignal(
		"/lifecycle",
		"subscribeLogicStep",
		FLEX_ARGS(
			FLEX_STRING(std::string(""))
			FLEX_STRING(std::string("logicStep"))
		)
	);
}

void LifeCycleInterface::onLogicStep(LogicStepMethod method) {
	logicMethod = method;
}

std::vector<uint8_t> LifeCycleInterface::logicStep(flexbuffers::Reference data, bool) {
	flexbuffers::Vector vec = data.AsVector();
	double delta = vec[0].AsDouble();
	double timeToRender = vec[1].AsDouble();
	logicMethod(delta, timeToRender);

	return std::vector<uint8_t>();
}

} // namespace StardustXRFusion
