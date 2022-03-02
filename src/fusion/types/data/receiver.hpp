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

class NonSpatialSender;

class NonSpatialReceiver : public Spatial {
public:
	explicit NonSpatialReceiver(Spatial *parent, Field &field, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity);
	explicit NonSpatialReceiver(NonSpatialSender *sender, std::string nodePath, std::string nodeName);\

	void getMask(std::function<void (flexbuffers::Reference)> callback);
	void getMask(std::function<void (flexbuffers::Map)> callback);
	void setMask(std::vector<uint8_t> mask);
	void setMask(std::function<void (flexbuffers::Builder &)> argsConstructor);

	void sendData(std::vector<uint8_t> data);
	void sendData(std::function<void (flexbuffers::Builder &)> dataConstructor);
	std::function<void(std::string, flexbuffers::Reference)> onDataReceived = [](std::string senderUUID, flexbuffers::Reference data){};
private:
	NonSpatialSender *sender;
	std::vector<uint8_t> dataReceived(flexbuffers::Reference data, bool);
};

} // namespace StardustXRFusion
