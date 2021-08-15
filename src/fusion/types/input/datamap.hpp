#pragma once

#include "../../sk_math.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace flexbuffers {
	class Map;
}

namespace StardustXRFusion {

class Datamap {
public:
	explicit Datamap(const flexbuffers::Map &flexDatamap);

	std::vector<std::string> keys() const;
	bool exists(std::string key);
	bool getBool(std::string key);
	int32_t getInt(std::string key);
	float getFloat(std::string key);
	SKMath::vec2 getVec2(std::string key);
	SKMath::vec3 getVec3(std::string key);

private:
	const flexbuffers::Map *flexDatamap;
};

} // namespace StardustXRFusion
