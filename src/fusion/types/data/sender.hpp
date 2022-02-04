#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "../spatial.hpp"
#include "../fields/field.hpp"
#include "receiver.hpp"

#include <flatbuffers/flexbuffers.h>

namespace StardustXRFusion {

class NonSpatialSender : public Spatial {
public:
	explicit NonSpatialSender(Spatial *parent, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity);

	void getReceivers(std::function<void(std::vector<NonSpatialReceiver> &)> callback);
};

} // namespace StardustXRFusion
