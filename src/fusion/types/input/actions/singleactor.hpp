#pragma once

#include "..//types/handinput.hpp"
#include "..//types/pointerinput.hpp"
#include "..//inputactionhandler.hpp"

namespace StardustXRFusion {

struct SingleActorAction : public InputActionHandler::Action {
	explicit SingleActorAction(bool captureOnTrigger = true, bool changeActor = true, InputActionHandler::Action *conditionAction = nullptr);
	std::function<bool(const std::string uuid, const PointerInput &, const Datamap &)> pointerActiveCondition = [](const std::string uuid, const PointerInput &pointer, const Datamap &datamap){return false;};
	std::function<bool(const std::string uuid, const HandInput &,    const Datamap &)> handActiveCondition    = [](const std::string uuid, const HandInput &hand,       const Datamap &datamap){return false;};
	InputActionHandler::Action *conditionAction;
	bool changeActor  = true;

	bool actorStarted = false;
	bool actorChanged = false;
	bool actorActing  = false;
	bool actorStopped = false;

	StardustXRFusion::InputActionHandler::InputMethod *actor = nullptr;

protected:
	std::vector<std::string> improperlyActed;
	bool actCondition(const std::string uuid, bool gesture);
	void update();
	std::string actorUUID;
};

}
