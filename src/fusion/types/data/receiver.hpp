#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "../spatial/spatial.hpp"
#include "../fields/field.hpp"
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/flexbuffers.h>

namespace StardustXRFusion {

class PulseSender;

class PulseReceiver : public Spatial {
public:
	explicit PulseReceiver(Spatial *parent, Field &field, Vec3 origin = Vec3::Zero, Quat rotation = Quat::Identity);
	explicit PulseReceiver(PulseSender *sender, std::string nodePath, std::string nodeName);

	void getMask(std::function<void (flexbuffers::Reference)> callback);
	void getMask(std::function<void (flexbuffers::Map)> callback);
	void setMask(std::vector<uint8_t> mask);
	void setMask(std::function<void (flexbuffers::Builder &)> argsConstructor);

	void sendData(std::vector<uint8_t> data);
	void sendData(std::function<void (flexbuffers::Builder &)> dataConstructor);
	std::function<void(std::string, flexbuffers::Reference)> onDataReceived = [](std::string senderUUID, flexbuffers::Reference data){};
private:
	PulseSender *sender;
	std::vector<uint8_t> dataReceived(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
