#pragma once

#include "../types/node.hpp"
#include "../scenegraph.hpp"

namespace StardustXRFusion {

typedef std::function<void(double, double)> LogicStepMethod;

class LifeCycleInterface : public Node {
public:
	explicit LifeCycleInterface();

	void onLogicStep(LogicStepMethod method);

private:
	LogicStepMethod logicMethod;
	std::vector<uint8_t> logicStep(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
