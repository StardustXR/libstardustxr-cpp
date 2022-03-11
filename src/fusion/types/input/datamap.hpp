#pragma once

#include "../../sk_math.hpp"
#include <cstdint>
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/flexbuffers.h>
#include <string>
#include <vector>

namespace StardustXRFusion {

class Datamap {
public:
	Datamap(const uint8_t *flexData, const size_t flexDataSize);
	Datamap(const Datamap &datamap);

	Datamap &operator=(const Datamap &other);

	std::vector<std::string> keys() const;
	bool exists(std::string key) const;
	bool getBool(std::string key) const;
	int32_t getInt(std::string key) const;
	float getFloat(std::string key) const;
	SKMath::vec2 getVec2(std::string key) const;
	SKMath::vec3 getVec3(std::string key) const;

private:
	std::vector<uint8_t> flexDataBuffer;
	flexbuffers::Map flexDatamap;
};

} // namespace StardustXRFusion
