#include "../../libstardustxr.hpp"
#include "../../flex.hpp"

#include "field.hpp"

namespace StardustXRFusion {

Field::Field() {}
Field::~Field() {}

void Field::distance(Spatial *space, vec3 point, std::function<void(float distance)> callback) {
	std::string spacePath = (space) ? space->getNodePath() : "";
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"distance",
		FLEX_ARGS(
			FLEX_STRING(spacePath)
			FLEX_VEC3(point)
		),
		[callback](flexbuffers::Reference data) {
			callback(data.AsFloat());
		}
	);
}

void Field::normal(Spatial *space, vec3 point, std::function<void (SKMath::vec3)> callback) {
	std::string spacePath = (space) ? space->getNodePath() : "";
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"normal",
		FLEX_ARGS(
			FLEX_STRING(spacePath)
			FLEX_VEC3(point)
		),
		[callback](flexbuffers::Reference data) {
			callback(SK_VEC3(data.AsVector()));
		}
	);
}

void Field::closestPoint(Spatial *space, SKMath::vec3 point, std::function<void (SKMath::vec3)> callback) {
	std::string spacePath = (space) ? space->getNodePath() : "";
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"distance",
		FLEX_ARGS(
			FLEX_STRING(spacePath)
			FLEX_VEC3(point)
		),
		[callback](flexbuffers::Reference data) {
			callback(SK_VEC3(data.AsVector()));
		}
	);
}

} // namespace StardustXRFusion
