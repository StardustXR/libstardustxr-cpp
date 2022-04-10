#include "singleactor.hpp"

namespace StardustXRFusion {

void SingleActorAction::update() {
	InputActionHandler::Action::update();

	if(startedActing.size() > 0 && !(!changeActor && actorUUID != "")) {
		auto newActor = startedActing.end()-1;
		if(newActor->uuid != actorUUID) {
			if(!actorActing)
				actorStarted = true;
			else
				actorChanged = true;
			actorActing = true;
			actor = newActor.base();
			actorUUID = actor->uuid;
			return;
		}
	}

	if(!actorActing && actor)
		actor = nullptr;
	auto stoppedActor = std::find(stoppedActing.begin(), stoppedActing.end(), actorUUID);
	if(actorActing && stoppedActor != stoppedActing.end()) {
		actor = stoppedActor.base();
		actorUUID = "";
		actorActing = false;
		actorStopped = true;
		return;
	}

	actorChanged = false;
	actorStarted = false;
	actorStopped = false;

	if(actorActing)
		actor = std::find(activelyActing.begin(), activelyActing.end(), actorUUID).base();
}

}
