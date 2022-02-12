#pragma once

#include "datamap.hpp"
#include "../spatial.hpp"
#include "../fields/field.hpp"
#include "../../sk_math.hpp"
#include "inputactions.hpp"

#include <map>

namespace flexbuffers {
	class Reference;
}

namespace StardustXRFusion {

class HandInput;
class PointerInput;

class InputHandler : public Spatial {
public:
	explicit InputHandler(Spatial *parent, Field &field, SKMath::vec3 origin, SKMath::quat orientation);
	explicit InputHandler(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation);
	~InputHandler();

	static void getInputHandlers(Spatial *space, bool excludeSelf, std::function<void(std::vector<InputActions> &)> callback);

	void setField(Field *field);

	std::function<bool(const std::string uuid, const PointerInput &, const Datamap &)> pointerHandlerMethod = [](const std::string uuid, const PointerInput &, const Datamap &) {
		return false;
	};
	std::function<bool(const std::string uuid, const HandInput &, const Datamap &)> handHandlerMethod = [](const std::string uuid, const HandInput &, const Datamap &) {
		return false;
	};

	std::map<std::string, std::function<void(void)>> actions;
	void updateActions();
	void runAction(std::string action);

private:
	std::vector<uint8_t> inputEvent(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
