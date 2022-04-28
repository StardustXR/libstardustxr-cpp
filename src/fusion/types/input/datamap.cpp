#include "datamap.hpp"
#include "../../flex.hpp"



namespace StardustXRFusion {

Datamap::Datamap(const uint8_t *flexData, const size_t flexDataSize) :
		flexDataBuffer(flexData, flexData+flexDataSize),
		flexDatamap(flexbuffers::GetRoot(flexDataBuffer).AsMap()) {}

Datamap::Datamap(const Datamap &datamap) :
	flexDataBuffer(datamap.flexDataBuffer),
	flexDatamap(flexbuffers::GetRoot(flexDataBuffer).AsMap()) {}

Datamap &Datamap::operator=(const Datamap &other) {
	this->flexDataBuffer = other.flexDataBuffer;
	this->flexDatamap = flexbuffers::GetRoot(flexDataBuffer).AsMap();
	return *this;
}

std::vector<std::string> Datamap::keys() const {
	flexbuffers::TypedVector flexKeys = flexDatamap.Keys();
	std::vector<std::string> keys;

	for(uint i=0; i<flexKeys.size(); ++i) {
		keys.push_back(flexKeys[i].AsString().str());
	}

	return keys;
}

bool Datamap::exists(std::string key) const {
	flexbuffers::Reference value = flexDatamap[key];

	return !value.IsNull();
}

bool Datamap::getBool(std::string key) const {
	flexbuffers::Reference value = flexDatamap[key];

	if(value.IsBool())
		return value.AsBool();
	else
		return false;
}

int32_t Datamap::getInt(std::string key) const {
	flexbuffers::Reference value = flexDatamap[key];

	if(value.IsInt())
		return value.AsInt32();
	else
		return 0;
}

float Datamap::getFloat(std::string key) const {
	flexbuffers::Reference value = flexDatamap[key];

	if(value.IsFloat())
		return value.AsFloat();
	else
		return 0.0f;
}

Vec2 Datamap::getVec2(std::string key) const {
	flexbuffers::Reference value = flexDatamap[key];

	if(value.IsTypedVector() && value.AsTypedVector().size() == 2)
		return STARDUST_VEC2(value.AsTypedVector());
	else
		return Vec2::Zero;
}

Vec3 Datamap::getVec3(std::string key) const {
	flexbuffers::Reference value = flexDatamap[key];

	if(value.IsTypedVector() && value.AsTypedVector().size() == 3)
		return STARDUST_VEC3(value.AsTypedVector());
	else
		return Vec3::Zero;
}

}
