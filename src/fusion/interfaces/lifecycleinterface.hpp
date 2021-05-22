#pragma once

#include <functional>
#include <flatbuffers/flexbuffers.h>

namespace StardustXRFusion {

typedef std::function<void(double, double)> LogicStepMethod;

class LifeCycleInterface {
public:
	explicit LifeCycleInterface();

	void onLogicStep(LogicStepMethod method);

private:
	LogicStepMethod logicMethod;
	std::vector<uint8_t> logicStep(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
