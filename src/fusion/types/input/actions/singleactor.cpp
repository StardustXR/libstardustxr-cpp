#include "singleactor.hpp"

namespace StardustXRFusion {

SingleActorAction::SingleActorAction(bool captureOnTrigger, bool changeActor, InputActionHandler::Action *conditionAction) :
Action(captureOnTrigger),
conditionAction(conditionAction),
changeActor(changeActor) {

	InputActionHandler::Action::pointerActiveCondition = [&](const std::string uuid, const PointerInput &pointer, const Datamap &datamap) {
		return actCondition(uuid, pointerActiveCondition(uuid, pointer, datamap));
	};
	InputActionHandler::Action::handActiveCondition = [&](const std::string uuid, const HandInput &hand, const Datamap &datamap) {
		return actCondition(uuid, handActiveCondition(uuid, hand, datamap));
	};
}

bool SingleActorAction::actCondition(const std::string uuid, bool gesture) {
	if(!conditionAction)
		return gesture;

	bool previouslyInRange = std::find(conditionAction->activelyActing.begin(), conditionAction->activelyActing.end(), uuid) != conditionAction->activelyActing.end();
	bool previouslyActed = std::find(this->activelyActing.begin(), this->activelyActing.end(), uuid) != this->activelyActing.end();
	bool isImproperlyActed = std::find(improperlyActed.begin(), improperlyActed.end(), uuid) != improperlyActed.end();
	if(!gesture && isImproperlyActed) {
		improperlyActed.erase(std::remove(improperlyActed.begin(), improperlyActed.end(), uuid));
		return false;
	}
	if(!isImproperlyActed && !previouslyInRange && !previouslyActed && gesture) {
		improperlyActed.push_back(uuid);
		return false;
	}

	return (previouslyInRange || previouslyActed) && gesture && !isImproperlyActed;
}

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
