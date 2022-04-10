#pragma once

#include "..//types/handinput.hpp"
#include "..//types/pointerinput.hpp"
#include "..//inputactionhandler.hpp"

namespace StardustXRFusion {

struct SingleActorAction : public InputActionHandler::Action {
	bool changeActor  = true;

	bool actorStarted = false;
	bool actorChanged = false;
	bool actorActing  = false;
	bool actorStopped = false;

	StardustXRFusion::InputActionHandler::InputMethod *actor = nullptr;

protected:
	void update();
	std::string actorUUID;
};

}
