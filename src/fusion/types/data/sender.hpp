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
	explicit PulseSender(Spatial *parent, Vec3 origin = Vec3::Zero, Quat rotation = Quat::Identity);

	void getReceivers(std::function<void(std::vector<PulseReceiver> &)> callback);
};

} // namespace StardustXRFusion
