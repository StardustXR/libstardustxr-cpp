#include "inputactionhandler.hpp"

namespace StardustXRFusion {

InputActionHandler::InputActionHandler(Spatial *parent, Field &field, Vec3 origin, Quat rotation) :
	InputHandler(parent, field, origin, rotation) {

	handHandlerMethod = std::bind(&InputActionHandler::handInputEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	pointerHandlerMethod = std::bind(&InputActionHandler::pointerInputEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

void InputActionHandler::update() {
	for(Action *action : actions) {
		action->update();
	}
}

bool InputActionHandler::pointerInputEvent(const std::string uuid, const PointerInput &pointer, const Datamap &datamap) {
	bool capture = false;
	for(Action *action : actions) {
		bool acted = action->pointerActiveCondition(uuid, pointer, datamap);
		if(acted) {
			if(action->captureOnTrigger)
				capture = true;

			action->queuedActiveInputs.emplace_back(uuid, datamap, new PointerInput(pointer), nullptr);
		}
	}
	return capture;
}

bool InputActionHandler::handInputEvent(const std::string uuid, const HandInput &hand, const Datamap &datamap) {
	bool capture = false;
	for(Action *action : actions) {
		bool acted = action->handActiveCondition(uuid, hand, datamap);
		if(acted) {
			if(action->captureOnTrigger)
				capture = true;

			action->queuedActiveInputs.emplace_back(uuid, datamap, nullptr, new HandInput(hand));
		}
	}
	return capture;
}

InputActionHandler::InputMethod::InputMethod(const std::string uuid, const Datamap datamap, PointerInput *pointer, HandInput *hand) :
	uuid(uuid),
	datamap(datamap),
	pointer(pointer),
	hand(hand) {}

InputActionHandler::InputMethod::InputMethod(const InputMethod &copyFrom) :
	InputMethod(copyFrom.uuid,
				copyFrom.datamap,
				copyFrom.pointer.get() ? new PointerInput(*copyFrom.pointer) : nullptr,
				copyFrom.hand   .get() ? new HandInput   (*copyFrom.hand   ) : nullptr) {}

void InputActionHandler::InputMethod::operator=(const InputMethod &other) {
	this->uuid = other.uuid;
	this->datamap = other.datamap;
	this->pointer.reset(other.pointer.get() ? new PointerInput(*other.pointer.get()) : nullptr);
	this->hand.reset(other.hand.get() ? new HandInput(*other.hand.get()) : nullptr);
}
bool InputActionHandler::InputMethod::operator<(const InputMethod &other) {
	return uuid < other.uuid;
}
bool InputActionHandler::InputMethod::operator==(const std::string &uuid) {
	return this->uuid == uuid;
}

InputActionHandler::Action::Action(bool captureOnTrigger) :
	captureOnTrigger(captureOnTrigger){}

void InputActionHandler::Action::update() {
//	std::sort(queuedActiveInputs.begin(), queuedActiveInputs.end(), [](InputMethod &a, InputMethod &b) {
//		return a.uuid < b.uuid;
//	});

	this->startedActing.clear();
	this->stoppedActing.clear();

	std::set_difference(queuedActiveInputs.begin(),  queuedActiveInputs.end(),
						activelyActing.begin(),      activelyActing.end(),
						std::inserter(startedActing, startedActing.begin()));

	std::set_difference(activelyActing.begin(),      activelyActing.end(),
						queuedActiveInputs.begin(),  queuedActiveInputs.end(),
						std::inserter(stoppedActing, stoppedActing.begin()));

	activelyActing = queuedActiveInputs;
	queuedActiveInputs.clear();
}

InputActionHandler::Action::~Action(){}

}
