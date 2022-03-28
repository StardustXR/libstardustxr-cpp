#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "../spatial/spatial.hpp"
#include "../fields/field.hpp"
#include "receiver.hpp"

namespace StardustXRFusion {

class PulseSender : public Spatial {
public:
	explicit PulseSender(Spatial *parent, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity);

	void getReceivers(std::function<void(std::vector<PulseReceiver> &)> callback);
};

} // namespace StardustXRFusion
